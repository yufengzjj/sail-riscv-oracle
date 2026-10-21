/* =============================================================================
 * shim.cpp — extern "C" ABI between Rust and the Sail C++ model class
 * (`hart::Model`, from `sail --cpp`; architectural state lives in members, so
 * each sailrv_new() is independent).
 *
 * PER-INSTANCE GLOBALS: the runtime keeps memory (sail_memory / sail_tags,
 * rts.c) and the parsed JSON configuration (sail_config.c — the model reads
 * it during execution, not only at init) in process globals. Each instance
 * owns its own copies; the Ctx RAII guard swaps them in around every call.
 * Correct only single-threaded — the Rust wrapper serializes all calls under
 * one mutex.
 *
 * FAILURES: a Sail assertion, pattern-match or configuration failure calls
 * sail_fatal (below), which throws; an uncaught Sail exception (e.g.
 * internal_error) only sets have_exception. Both poison the instance:
 * sailrv_error() returns the message, and the failed call and every later
 * one return 0/false without running the model. No C++ exception may leave
 * an extern "C" function.
 *
 * NAME MANGLING: Sail prefixes top-level names with `z` and escapes a literal
 * 'z' to "zz".
 * ===========================================================================*/

#include "sail.h"
#include "sail_config.h"
#include "cJSON.h"
#include "sail_riscv_model.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

/* Memory-model globals + accessors from rts.c (not exposed in rts.h).
 * read/write_mem are byte-addressed, little-endian (byte at `address` = LSB)
 * and are exactly what the model's loads/stores decompose into. */
extern "C" {
struct block;
struct tag_block;
extern struct block *sail_memory;
extern struct tag_block *sail_tags;
void kill_mem(void);
uint64_t read_mem(uint64_t address);
void write_mem(uint64_t address, uint64_t byte);
bool sail_addr_mapped(uint64_t address);
}

namespace {

/* Kinds shared with src/lib.rs (`Change`). */
enum ChangeKind : uint32_t {
    CH_XREG = 1,
    CH_FREG = 2,
    CH_VREG = 3,
    CH_CSR = 4,
    CH_MEM_READ = 5,
    CH_MEM_WRITE = 6,
    CH_MEM_FAULT = 7,
    CH_TRAP = 8,
    CH_XRET = 9,
};

struct Change {
    uint32_t kind;
    uint32_t index;
    uint64_t addr;
    uint64_t value;
    std::vector<uint8_t> data;
    std::string access;
};

std::vector<uint8_t> lbits_bytes(lbits v, size_t nbytes) {
    size_t need = (mpz_sizeinbase(*v.bits, 2) + 7) / 8;
    std::vector<uint8_t> out(need > nbytes ? need : nbytes, 0);
    size_t count = 0;
    mpz_export(out.data(), &count, -1, 1, 0, 0, *v.bits);
    out.resize(nbytes);
    return out;
}

uint64_t config_u64(cJSON *root, std::initializer_list<const char *> path, uint64_t dflt) {
    cJSON *j = root;
    for (const char *k : path) {
        j = cJSON_GetObjectItemCaseSensitive(j, k);
    }
    return cJSON_IsNumber(j) ? (uint64_t)j->valuedouble : dflt;
}

bool config_bool(cJSON *root, std::initializer_list<const char *> path) {
    cJSON *j = root;
    for (const char *k : path) {
        j = cJSON_GetObjectItemCaseSensitive(j, k);
    }
    return cJSON_IsTrue(j);
}

/* The model with sail-riscv's platform callbacks implemented for an oracle:
 * deterministic (seeded entropy, no terminal or log output) and recording a
 * change list while a step runs. Reservation and event-counter handling
 * follow c_emulator/riscv_model_impl.cpp. */
class OracleModel final : public hart::Model {
public:
    using Privilege = hart::zPrivilege;
    using Event = hart::zEvent;

    bool rvfi = false;
    bool recording = false;
    bool retired = false;
    std::vector<Change> changes;

    void init_platform(cJSON *config) {
        uint64_t exp = config_u64(config, {"platform", "reservation", "reservation_set_size_exp"}, 3);
        m_reservation_set_addr_mask = ~((UINT64_C(1) << exp) - 1);
        m_reservation_require_exact_addr =
            config_bool(config, {"platform", "reservation", "require_exact_reservation_addr"});
        m_reservation_invalidate_on_same_hart_store =
            config_bool(config, {"platform", "reservation", "invalidate_on_same_hart_store"});
    }

    void seed(uint64_t s) { m_gen64.seed(s); }

    void begin_step() {
        changes.clear();
        retired = false;
        recording = true;
    }

    void end_step() { recording = false; }

    void reserve(uint64_t addr) {
        m_reservation_addr = addr;
        m_reservation = addr & m_reservation_set_addr_mask;
        m_reservation_valid = true;
    }

    void unreserve() { m_reservation_valid = false; }

    bool reservation(uint64_t *addr) const {
        *addr = m_reservation_addr;
        return m_reservation_valid;
    }

private:
    void record(uint32_t kind, uint32_t index, uint64_t addr, uint64_t value,
                std::vector<uint8_t> data = {}, const char *access = nullptr) {
        if (!recording) return;
        changes.push_back({kind, index, addr, value, std::move(data), access ? access : ""});
    }

    unit mem_write_callback(const char *type, sbits paddr, int64_t width, lbits value) override {
        record(CH_MEM_WRITE, 0, paddr.bits, 0, lbits_bytes(value, (size_t)width), type);
        if (m_reservation_invalidate_on_same_hart_store && match_reservation(paddr)) {
            cancel_reservation(UNIT);
        }
        return UNIT;
    }

    unit mem_read_callback(const char *type, sbits paddr, int64_t width, lbits value) override {
        record(CH_MEM_READ, 0, paddr.bits, 0, lbits_bytes(value, (size_t)width), type);
        return UNIT;
    }

    unit mem_exception_callback(sbits paddr, uint64_t num_of_exception) override {
        record(CH_MEM_FAULT, 0, paddr.bits, num_of_exception);
        return UNIT;
    }

    unit xreg_full_write_callback(const_sail_string, sbits reg, sbits value) override {
        record(CH_XREG, (uint32_t)reg.bits, 0, value.bits);
        return UNIT;
    }

    unit freg_write_callback(unsigned reg, sbits value) override {
        record(CH_FREG, reg, 0, value.bits);
        return UNIT;
    }

    unit csr_full_write_callback(const_sail_string, unsigned reg, sbits value) override {
        record(CH_CSR, reg, 0, value.bits);
        return UNIT;
    }

    unit vreg_write_callback(unsigned reg, lbits value) override {
        record(CH_VREG, reg, 0, 0, lbits_bytes(value, (size_t)((value.len + 7) / 8)));
        return UNIT;
    }

    unit trap_callback(bool is_interrupt, fbits cause) override {
        record(CH_TRAP, is_interrupt ? 1 : 0, 0, cause);
        return UNIT;
    }

    unit xret_callback(bool is_mret) override {
        record(CH_XRET, is_mret ? 1 : 0, 0, 0);
        return UNIT;
    }

    unit instret_callback(unit) override {
        retired = true;
        return UNIT;
    }

    mach_bits plat_get_16_random_bits(unit) override { return m_gen64() & 0xFFFF; }

    unit load_reservation(sbits addr, uint64_t) override {
        reserve(addr.bits);
        return UNIT;
    }

    bool match_reservation(sbits addr) override {
        return m_reservation_valid &&
               (m_reservation_require_exact_addr
                    ? addr.bits == m_reservation_addr
                    : (m_reservation & m_reservation_set_addr_mask) ==
                          (addr.bits & m_reservation_set_addr_mask));
    }

    unit cancel_reservation(unit) override {
        unreserve();
        return UNIT;
    }

    bool valid_reservation(unit) override { return m_reservation_valid; }

    bool validate_event_selectors(unit) override {
        std::set<uint64_t> selectors;
        std::map<Event, uint64_t> event_map;
        int64_t width = zevent_selector_width(UNIT);
        uint64_t mask = width == 64 ? ~UINT64_C(0) : (UINT64_C(1) << width) - 1;
        int idx = 0;
        for (const auto *ent = zplatform_event_selectors; ent != nullptr; ent = ent->tl, ++idx) {
            Event ev = ent->hd.zevent;
            uint64_t sel = ent->hd.zselector;
            if (sel == 0 || (sel & mask) != sel || selectors.count(sel) || event_map.count(ev)) {
                fprintf(stderr, "platform.event_selectors entry #%d is invalid\n", idx);
                return false;
            }
            selectors.insert(sel);
            event_map[ev] = sel;
        }
        m_event_to_selector = event_map;
        return true;
    }

    unit event_csr_write_callback(int64_t index, uint64_t old_selector, uint64_t new_selector) override {
        auto old_ent = m_selector_to_hpmidxs.find(old_selector);
        if (old_ent != m_selector_to_hpmidxs.end()) {
            old_ent->second.erase(index);
        }
        if (new_selector == 0) return UNIT;
        for (const auto &[ev, sel] : m_event_to_selector) {
            if (sel == new_selector) {
                m_selector_to_hpmidxs[new_selector].insert(index);
                break;
            }
        }
        return UNIT;
    }

    unit event_callback(Event ev, Privilege priv) override {
        m_generated_events.emplace_back(ev, priv);
        return UNIT;
    }

    unit dispatch_events(unit) override {
        for (const auto &[ev, priv] : m_generated_events) {
            auto sel = m_event_to_selector.find(ev);
            if (sel == m_event_to_selector.end()) continue;
            auto idxs = m_selector_to_hpmidxs.find(sel->second);
            if (idxs == m_selector_to_hpmidxs.end()) continue;
            for (int64_t idx : idxs->second) {
                zdispatchEventCounter(idx, priv);
            }
        }
        m_generated_events.clear();
        return UNIT;
    }

    unit plat_term_write(mach_bits) override { return UNIT; }

    bool sys_enable_experimental_extensions(unit) override { return true; }

    unit print_string(const_sail_string prefix, const_sail_string msg) override {
        fprintf(stderr, "%s%s\n", prefix, msg);
        return UNIT;
    }

    unit print_log(const_sail_string) override { return UNIT; }
    unit print_log_instr(const_sail_string, uint64_t) override { return UNIT; }
    unit print_step(unit) override { return UNIT; }

    bool get_config_rvfi(unit) override { return rvfi; }

    uint64_t m_reservation = 0;
    uint64_t m_reservation_addr = 0;
    bool m_reservation_valid = false;
    uint64_t m_reservation_set_addr_mask = 0;
    bool m_reservation_require_exact_addr = false;
    bool m_reservation_invalidate_on_same_hart_store = false;

    std::map<Event, uint64_t> m_event_to_selector;
    std::map<uint64_t, std::set<int64_t>> m_selector_to_hpmidxs;
    std::vector<std::pair<Event, Privilege>> m_generated_events;

    std::mt19937_64 m_gen64{0};
};

struct OracleInstance {
    OracleModel m;
    struct block *memory = nullptr;
    struct tag_block *tags = nullptr;
    cJSON *config = nullptr;
    int64_t step_no = 0;
    std::string error; // non-empty once poisoned
};

OracleInstance *cast(void *h) { return static_cast<OracleInstance *>(h); }

/* Swap the instance's memory lists and config tree into the runtime globals
 * for the call, save the (possibly grown) memory heads back on exit. */
class Ctx {
    OracleInstance *inst;
    void *prev_config;

public:
    explicit Ctx(OracleInstance *i) : inst(i) {
        sail_memory = i->memory;
        sail_tags = i->tags;
        prev_config = sail_config_swap(i->config);
    }
    ~Ctx() {
        inst->memory = sail_memory;
        inst->tags = sail_tags;
        sail_config_swap(prev_config);
    }
};

void set_err(char *err, size_t len, const std::string &msg) {
    if (err != nullptr && len > 0) {
        snprintf(err, len, "%s", msg.c_str());
    }
}

/* Turn an uncaught Sail exception into a C++ one. The model leaves a step
 * half done when it throws, so the caller must poison the instance. */
void check_sail_exception(OracleModel &m) {
    if (!m.have_exception) return;
    m.have_exception = false;
    const hart::zexception &e = *m.current_exception;
    std::string msg = "uncaught Sail exception: ";
    switch (e.kind) {
    case hart::Kind_zError_internal_error:
        msg += std::string("internal error: ") + e.variants.zError_internal_error;
        break;
    case hart::Kind_zError_not_implemented:
        msg += std::string("not implemented: ") + e.variants.zError_not_implemented;
        break;
    case hart::Kind_zError_reserved_behavior:
        msg += std::string("reserved behavior: ") + e.variants.zError_reserved_behavior;
        break;
    default:
        msg += "kind " + std::to_string((int)e.kind);
        break;
    }
    msg += std::string(" (thrown at ") + *m.throw_location + ")";
    throw std::runtime_error(msg);
}

void poison(OracleInstance *o, const char *msg) {
    o->error = (msg != nullptr && *msg != '\0') ? msg : "unknown model failure";
}

/* Run `body` on the instance's model with its globals swapped in. Returns
 * false (doing nothing) if the instance is poisoned, or after poisoning it
 * if `body` fails. */
template <class F> bool guarded(OracleInstance *o, F &&body) {
    if (!o->error.empty()) return false;
    try {
        Ctx ctx(o);
        body(o->m);
        check_sail_exception(o->m);
        return true;
    } catch (const std::exception &e) {
        poison(o, e.what());
    } catch (...) {
        poison(o, "unknown C++ exception in the model");
    }
    return false;
}

bool is_index(const std::string &s) {
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}

/* Replace (or create) the item at a dotted path with parsed JSON `value`. In
 * an array, an all-digit segment is an index and "-" appends. */
bool apply_override(cJSON *root, const char *dotted, const char *value, std::string &why) {
    cJSON *v = cJSON_Parse(value);
    if (v == nullptr) {
        why = std::string("override for '") + dotted + "' is not valid JSON: " + value;
        return false;
    }
    std::string path(dotted);
    cJSON *node = root;
    size_t start = 0;
    while (true) {
        size_t dot = path.find('.', start);
        bool last = dot == std::string::npos;
        std::string key = path.substr(start, last ? std::string::npos : dot - start);
        cJSON *next = nullptr;
        if (cJSON_IsObject(node) && !key.empty()) {
            next = cJSON_GetObjectItemCaseSensitive(node, key.c_str());
            if (last) {
                if (next != nullptr) {
                    cJSON_ReplaceItemInObjectCaseSensitive(node, key.c_str(), v);
                } else {
                    cJSON_AddItemToObject(node, key.c_str(), v);
                }
                return true;
            }
            if (next == nullptr) {
                next = cJSON_AddObjectToObject(node, key.c_str());
            }
        } else if (cJSON_IsArray(node) && key == "-") {
            if (last) {
                cJSON_AddItemToArray(node, v);
                return true;
            }
            next = cJSON_CreateObject();
            cJSON_AddItemToArray(node, next);
        } else if (cJSON_IsArray(node) && is_index(key)) {
            int size = cJSON_GetArraySize(node);
            int index = key.size() > 9 ? INT32_MAX : std::stoi(key);
            if (index >= size) {
                cJSON_Delete(v);
                why = std::string("override path '") + dotted + "': index " + key +
                      " is out of range (the array has " + std::to_string(size) + " elements)";
                return false;
            }
            if (last) {
                cJSON_ReplaceItemInArray(node, index, v);
                return true;
            }
            next = cJSON_GetArrayItem(node, index);
        } else {
            cJSON_Delete(v);
            why = std::string("override path '") + dotted +
                  "' does not name an object member or array element";
            return false;
        }
        node = next;
        start = dot + 1;
    }
}

uint64_t parse_hex(const cJSON *item) {
    const char *s = cJSON_GetStringValue(item);
    if (s == nullptr) return 0;
    std::string digits;
    for (const char *p = s; *p != '\0'; p++) {
        if (*p != '_') digits += *p;
    }
    return strtoull(digits.c_str(), nullptr, 0);
}

void set_hex(cJSON *bits, uint64_t value) {
    char text[32];
    snprintf(text, sizeof text, "0x%llx", (unsigned long long)value);
    cJSON_ReplaceItemInObjectCaseSensitive(bits, "value", cJSON_CreateString(text));
}

/* Insert a copy of the first MainMemory region over [base, base + size),
 * before the first region with a higher base: the model requires the regions
 * sorted by address. */
bool add_ram(cJSON *root, uint64_t base, uint64_t size, std::string &why) {
    cJSON *regions = cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(root, "memory"), "regions");
    cJSON *ram = nullptr;
    cJSON *r = nullptr;
    cJSON_ArrayForEach(r, regions) {
        cJSON *type = cJSON_GetObjectItemCaseSensitive(
            cJSON_GetObjectItemCaseSensitive(r, "attributes"), "mem_type");
        if (cJSON_IsString(type) && strcmp(type->valuestring, "MainMemory") == 0) {
            ram = r;
            break;
        }
    }
    if (!cJSON_IsArray(regions) || ram == nullptr) {
        why = "add_ram: the configuration has no MainMemory region in memory.regions";
        return false;
    }
    cJSON *copy = cJSON_Duplicate(ram, true);
    set_hex(cJSON_GetObjectItemCaseSensitive(copy, "base"), base);
    set_hex(cJSON_GetObjectItemCaseSensitive(copy, "size"), size);
    int at = 0;
    cJSON_ArrayForEach(r, regions) {
        if (parse_hex(cJSON_GetObjectItemCaseSensitive(cJSON_GetObjectItemCaseSensitive(r, "base"),
                                                       "value")) > base) {
            break;
        }
        at++;
    }
    if (at < cJSON_GetArraySize(regions)) {
        cJSON_InsertItemInArray(regions, at, copy);
    } else {
        cJSON_AddItemToArray(regions, copy);
    }
    return true;
}

uint32_t run_step(OracleInstance *o) {
    sail_int step_no;
    CREATE(sail_int)(&step_no);
    CONVERT_OF(sail_int, mach_int)(&step_no, (mach_int)o->step_no);
    /* A WFI/WRS that is not configured as a nop leaves the hart waiting; the
     * second try_step (exit_wait) completes it, so one oracle step is always
     * one instruction. */
    bool waiting = o->m.ztry_step(step_no, true);
    check_sail_exception(o->m);
    if (waiting) {
        waiting = o->m.ztry_step(step_no, true);
    }
    KILL(sail_int)(&step_no);
    o->step_no++;
    return (o->m.retired ? 1u : 0u) | (waiting ? 2u : 0u);
}

/* Free everything of an instance whose model_init completed. */
void destroy(OracleInstance *o) {
    try {
        Ctx ctx(o);
        kill_mem(); // frees THIS instance's memory
        o->m.have_exception = false; // model_fini exits the process otherwise
        o->m.model_fini();           // refcounted cleanup_rts inside
    } catch (...) {
    }
    cJSON_Delete(o->config);
    delete o;
}

void *new_instance(const char *json, const char *const *keys, const char *const *values,
                   size_t n_overrides, const uint64_t *ram, size_t n_ram, uint64_t pc_reset,
                   char *err, size_t err_len) {
    std::string text(json);
    cJSON_Minify(text.data());
    cJSON *config = cJSON_Parse(text.c_str());
    if (config == nullptr) {
        set_err(err, err_len, "configuration is not valid JSON");
        return nullptr;
    }
    for (size_t i = 0; i < n_overrides; i++) {
        std::string why;
        if (!apply_override(config, keys[i], values[i], why)) {
            cJSON_Delete(config);
            set_err(err, err_len, why);
            return nullptr;
        }
    }
    for (size_t i = 0; i < n_ram; i++) {
        std::string why;
        if (!add_ram(config, ram[2 * i], ram[2 * i + 1], why)) {
            cJSON_Delete(config);
            set_err(err, err_len, why);
            return nullptr;
        }
    }

    OracleInstance *o = new OracleInstance();
    o->config = config;
    bool inited = false;
    bool valid = false;
    bool failed = true;
    std::string failure = "unknown C++ exception in the model";
    try {
        Ctx ctx(o);
        o->m.init_platform(config);
        /* model_init reads these before it creates the GMP scratch shared by
         * all instances; failing there would leave the scratch refcounted
         * but never created, so read them first. */
        o->m.sail_set_abstract_asidlen();
        o->m.sail_set_abstract_base_E_enabled();
        o->m.sail_set_abstract_elen_exp();
        o->m.sail_set_abstract_ext_d_supported();
        o->m.sail_set_abstract_geilen();
        o->m.sail_set_abstract_num_triggers();
        o->m.sail_set_abstract_physaddr_bits();
        o->m.sail_set_abstract_plat_hpmcounter_width_bits();
        o->m.sail_set_abstract_plat_hpmevent_width_bits();
        o->m.sail_set_abstract_sdtrig_mcontrol6_maskmax();
        o->m.sail_set_abstract_vlen_exp();
        o->m.sail_set_abstract_vmidlen();
        o->m.sail_set_abstract_xlen();
        o->m.model_init(); // setup_rts() refcounted
        inited = true;
        valid = o->m.zconfig_is_valid(UNIT);
        check_sail_exception(o->m);
        if (valid) {
            o->m.zset_pc_reset_address(pc_reset);
            o->m.zinit_model("");
            o->m.zoracle_init(UNIT);
            check_sail_exception(o->m);
        }
        failed = false;
    } catch (const std::exception &e) {
        failure = e.what();
    } catch (...) {
    }
    if (failed || !valid) {
        if (inited) {
            destroy(o);
        } else {
            {
                Ctx ctx(o);
                kill_mem();
            }
            cJSON_Delete(o->config);
            /* No model_fini after a half-run model_init: it would kill
             * letbinds never created. ~Model is empty, so deleting only leaks
             * the letbinds' GMP data and keeps the shared refcounts raised. */
            delete o;
        }
        set_err(err, err_len,
                failed ? "model failure while reading the configuration: " + failure
                       : "configuration rejected by the model (details on stdout)");
        return nullptr;
    }
    return o;
}

} // namespace

extern "C" {

void sail_fatal(const char *msg) {
    throw std::runtime_error(msg != nullptr ? msg : "sail_fatal");
}

/* `json` may contain // comments. `ram` holds `n_ram` (base, size) pairs of
 * main memory added after the overrides. Returns null (and a message in
 * `err`) if the JSON or the resulting configuration is invalid, or the model
 * fails while reading it. */
void *sailrv_new(const char *json, const char *const *keys, const char *const *values,
                 size_t n_overrides, const uint64_t *ram, size_t n_ram, uint64_t pc_reset,
                 char *err, size_t err_len) {
    try {
        return new_instance(json, keys, values, n_overrides, ram, n_ram, pc_reset, err, err_len);
    } catch (...) {
        if (err != nullptr && err_len > 0) {
            snprintf(err, err_len, "out of memory");
        }
        return nullptr;
    }
}

/* Always succeeds, also for a poisoned instance. */
void sailrv_free(void *h) { destroy(cast(h)); }

/* Null while the instance is healthy; after a model failure, its message
 * (valid until sailrv_free). */
const char *sailrv_error(void *h) {
    OracleInstance *o = cast(h);
    return o->error.empty() ? nullptr : o->error.c_str();
}

void sailrv_seed(void *h, uint64_t seed) { cast(h)->m.seed(seed); }

/* Returns bit0 = retired, bit1 = still waiting (WFI/WRS). */
uint32_t sailrv_step(void *h, uint32_t opcode) {
    OracleInstance *o = cast(h);
    uint32_t r = 0;
    guarded(o, [&](OracleModel &m) {
        m.begin_step();
        m.rvfi = true; // fetch takes the injected rvfi_instruction instead of memory
        m.zrvfi_set_instr_packet((uint64_t)opcode);
        r = run_step(o);
        m.rvfi = false;
        m.end_step();
    });
    return r;
}

uint32_t sailrv_step_fetch(void *h) {
    OracleInstance *o = cast(h);
    uint32_t r = 0;
    guarded(o, [&](OracleModel &m) {
        m.begin_step();
        r = run_step(o);
        m.end_step();
    });
    return r;
}

size_t sailrv_change_count(void *h) { return cast(h)->m.changes.size(); }

void sailrv_change_get(void *h, size_t i, uint32_t *kind, uint32_t *index, uint64_t *addr,
                       uint64_t *value, size_t *data_len) {
    const Change &c = cast(h)->m.changes[i];
    *kind = c.kind;
    *index = c.index;
    *addr = c.addr;
    *value = c.value;
    *data_len = c.data.size();
}

void sailrv_change_data(void *h, size_t i, uint8_t *buf) {
    const Change &c = cast(h)->m.changes[i];
    memcpy(buf, c.data.data(), c.data.size());
}

/* Access-type string of a memory change ("" for others); valid until the next step. */
const char *sailrv_change_access(void *h, size_t i) { return cast(h)->m.changes[i].access.c_str(); }

#define GETTER(name)                                                                              \
    uint64_t sailrv_##name(void *h) {                                                             \
        uint64_t r = 0;                                                                           \
        guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_##name(UNIT); });                    \
        return r;                                                                                 \
    }
#define SETTER(name)                                                                              \
    void sailrv_##name(void *h, uint64_t value) {                                                 \
        guarded(cast(h), [&](OracleModel &m) { m.zoracle_##name(value); });                       \
    }

GETTER(xlen)
GETTER(flen)
GETTER(vlen)
GETTER(elen)
GETTER(get_pc)
SETTER(set_pc)
GETTER(get_fcsr)
SETTER(set_fcsr)
GETTER(get_vl)
SETTER(set_vl)
GETTER(get_vtype)
SETTER(set_vtype)
GETTER(get_vstart)
SETTER(set_vstart)
GETTER(get_vcsr)
SETTER(set_vcsr)
GETTER(get_priv)
SETTER(set_priv)

bool sailrv_has_fregs(void *h) {
    bool r = false;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_has_fregs(UNIT); });
    return r;
}

bool sailrv_has_vregs(void *h) {
    bool r = false;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_has_vregs(UNIT); });
    return r;
}

uint64_t sailrv_get_x(void *h, uint32_t n) {
    uint64_t r = 0;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_get_x(n & 0x1f); });
    return r;
}

void sailrv_set_x(void *h, uint32_t n, uint64_t value) {
    guarded(cast(h), [&](OracleModel &m) { m.zoracle_set_x(n & 0x1f, value); });
}

uint64_t sailrv_get_f(void *h, uint32_t n) {
    uint64_t r = 0;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_get_f(n & 0x1f); });
    return r;
}

void sailrv_set_f(void *h, uint32_t n, uint64_t value) {
    guarded(cast(h), [&](OracleModel &m) { m.zoracle_set_f(n & 0x1f, value); });
}

uint64_t sailrv_get_v(void *h, uint32_t n, uint32_t chunk) {
    uint64_t r = 0;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_get_v_chunk(n & 0x1f, chunk & 0xffff); });
    return r;
}

void sailrv_set_v(void *h, uint32_t n, uint32_t chunk, uint64_t value) {
    guarded(cast(h), [&](OracleModel &m) { m.zoracle_set_v_chunk(n & 0x1f, chunk & 0xffff, value); });
}

bool sailrv_csr_readable(void *h, uint32_t csr) {
    bool r = false;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_csr_readable(csr & 0xfff); });
    return r;
}

uint64_t sailrv_read_csr(void *h, uint32_t csr) {
    uint64_t r = 0;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_read_csr(csr & 0xfff); });
    return r;
}

bool sailrv_write_csr(void *h, uint32_t csr, uint64_t value) {
    bool r = false;
    guarded(cast(h), [&](OracleModel &m) { r = m.zoracle_write_csr(csr & 0xfff, value); });
    return r;
}

/* Copies the canonical ISA string (NUL-terminated, truncated to `len`);
 * returns its full length. */
size_t sailrv_isa_string(void *h, char *buf, size_t len) {
    std::string s;
    guarded(cast(h), [&](OracleModel &m) {
        sail_string str = nullptr;
        CREATE(sail_string)(&str);
        m.zgenerate_canonical_isa_string(&str, UNIT);
        s = str;
        KILL(sail_string)(&str);
    });
    if (len > 0) {
        snprintf(buf, len, "%s", s.c_str());
    }
    return s.size();
}

uint8_t sailrv_read_byte(void *h, uint64_t addr) {
    uint8_t r = 0;
    guarded(cast(h), [&](OracleModel &) { r = (uint8_t)read_mem(addr); });
    return r;
}

void sailrv_write_byte(void *h, uint64_t addr, uint8_t byte) {
    guarded(cast(h), [&](OracleModel &) { write_mem(addr, (uint64_t)byte); });
}

bool sailrv_is_mapped(void *h, uint64_t addr) {
    bool r = false;
    guarded(cast(h), [&](OracleModel &) { r = sail_addr_mapped(addr); });
    return r;
}

/* Setting acts like an LR at physical address `addr`; clearing like a
 * cancelled reservation. */
void sailrv_set_reservation(void *h, bool valid, uint64_t addr) {
    guarded(cast(h), [&](OracleModel &m) {
        if (valid) {
            m.reserve(addr);
        } else {
            m.unreserve();
        }
    });
}

/* Whether a reservation is held; `*addr` = the exact address it was made at. */
bool sailrv_get_reservation(void *h, uint64_t *addr) {
    bool r = false;
    *addr = 0;
    guarded(cast(h), [&](OracleModel &m) { r = m.reservation(addr); });
    return r;
}

} // extern "C"
