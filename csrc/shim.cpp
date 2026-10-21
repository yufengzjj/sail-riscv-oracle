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
 * NAME MANGLING: Sail prefixes top-level names with `z` and escapes a literal
 * 'z' to "zz".
 * ===========================================================================*/

#include "sail.h"
#include "sail_config.h"
#include "cJSON.h"
#include "sail_riscv_model.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <map>
#include <random>
#include <set>
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
        m_reservation_addr = addr.bits;
        m_reservation = addr.bits & m_reservation_set_addr_mask;
        m_reservation_valid = true;
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
        m_reservation_valid = false;
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

/* Replace (or create) the item at a dotted path with parsed JSON `value`. */
bool apply_override(cJSON *root, const char *dotted, const char *value, std::string &why) {
    cJSON *v = cJSON_Parse(value);
    if (v == nullptr) {
        why = std::string("override for '") + dotted + "' is not valid JSON: " + value;
        return false;
    }
    std::string path(dotted);
    cJSON *obj = root;
    size_t start = 0;
    while (true) {
        size_t dot = path.find('.', start);
        std::string key = path.substr(start, dot == std::string::npos ? std::string::npos : dot - start);
        if (!cJSON_IsObject(obj) || key.empty()) {
            cJSON_Delete(v);
            why = std::string("override path '") + dotted + "' does not name an object member";
            return false;
        }
        if (dot == std::string::npos) {
            if (cJSON_GetObjectItemCaseSensitive(obj, key.c_str()) != nullptr) {
                cJSON_ReplaceItemInObjectCaseSensitive(obj, key.c_str(), v);
            } else {
                cJSON_AddItemToObject(obj, key.c_str(), v);
            }
            return true;
        }
        cJSON *next = cJSON_GetObjectItemCaseSensitive(obj, key.c_str());
        if (next == nullptr) {
            next = cJSON_AddObjectToObject(obj, key.c_str());
        }
        obj = next;
        start = dot + 1;
    }
}

uint32_t run_step(OracleInstance *o) {
    sail_int step_no;
    CREATE(sail_int)(&step_no);
    CONVERT_OF(sail_int, mach_int)(&step_no, (mach_int)o->step_no);
    /* A WFI/WRS that is not configured as a nop leaves the hart waiting; the
     * second try_step (exit_wait) completes it, so one oracle step is always
     * one instruction. */
    bool waiting = o->m.ztry_step(step_no, true);
    if (waiting) {
        waiting = o->m.ztry_step(step_no, true);
    }
    KILL(sail_int)(&step_no);
    o->step_no++;
    return (o->m.retired ? 1u : 0u) | (waiting ? 2u : 0u);
}

} // namespace

extern "C" {

/* `json` may contain // comments. Returns null (and a message in `err`) if the
 * JSON or the resulting configuration is invalid. */
void *sailrv_new(const char *json, const char *const *keys, const char *const *values,
                 size_t n_overrides, uint64_t pc_reset, char *err, size_t err_len) {
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

    OracleInstance *o = new OracleInstance();
    o->config = config;
    bool valid;
    {
        Ctx ctx(o);
        o->m.init_platform(config);
        o->m.model_init(); // setup_rts() refcounted
        valid = o->m.zconfig_is_valid(UNIT);
        if (valid) {
            o->m.zset_pc_reset_address(pc_reset);
            o->m.zinit_model("");
            o->m.zoracle_init(UNIT);
        } else {
            kill_mem();
            o->m.model_fini();
        }
    }
    if (!valid) {
        cJSON_Delete(o->config);
        delete o;
        set_err(err, err_len, "configuration rejected by the model (details on stdout)");
        return nullptr;
    }
    return o;
}

void sailrv_free(void *h) {
    OracleInstance *o = cast(h);
    {
        Ctx ctx(o);
        kill_mem();        // frees THIS instance's memory
        o->m.model_fini(); // refcounted cleanup_rts inside
    }
    cJSON_Delete(o->config);
    delete o;
}

void sailrv_seed(void *h, uint64_t seed) { cast(h)->m.seed(seed); }

/* Returns bit0 = retired, bit1 = still waiting (WFI/WRS). */
uint32_t sailrv_step(void *h, uint32_t opcode) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    o->m.begin_step();
    o->m.rvfi = true; // fetch takes the injected rvfi_instruction instead of memory
    o->m.zrvfi_set_instr_packet((uint64_t)opcode);
    uint32_t r = run_step(o);
    o->m.rvfi = false;
    o->m.end_step();
    return r;
}

uint32_t sailrv_step_fetch(void *h) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    o->m.begin_step();
    uint32_t r = run_step(o);
    o->m.end_step();
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
        OracleInstance *o = cast(h);                                                              \
        Ctx ctx(o);                                                                               \
        return o->m.zoracle_##name(UNIT);                                                         \
    }
#define SETTER(name)                                                                              \
    void sailrv_##name(void *h, uint64_t value) {                                                 \
        OracleInstance *o = cast(h);                                                              \
        Ctx ctx(o);                                                                               \
        o->m.zoracle_##name(value);                                                               \
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
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_has_fregs(UNIT);
}

bool sailrv_has_vregs(void *h) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_has_vregs(UNIT);
}

uint64_t sailrv_get_x(void *h, uint32_t n) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_get_x(n & 0x1f);
}

void sailrv_set_x(void *h, uint32_t n, uint64_t value) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    o->m.zoracle_set_x(n & 0x1f, value);
}

uint64_t sailrv_get_f(void *h, uint32_t n) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_get_f(n & 0x1f);
}

void sailrv_set_f(void *h, uint32_t n, uint64_t value) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    o->m.zoracle_set_f(n & 0x1f, value);
}

uint64_t sailrv_get_v(void *h, uint32_t n, uint32_t chunk) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_get_v_chunk(n & 0x1f, chunk & 0xffff);
}

void sailrv_set_v(void *h, uint32_t n, uint32_t chunk, uint64_t value) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    o->m.zoracle_set_v_chunk(n & 0x1f, chunk & 0xffff, value);
}

bool sailrv_csr_readable(void *h, uint32_t csr) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_csr_readable(csr & 0xfff);
}

uint64_t sailrv_read_csr(void *h, uint32_t csr) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_read_csr(csr & 0xfff);
}

bool sailrv_write_csr(void *h, uint32_t csr, uint64_t value) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return o->m.zoracle_write_csr(csr & 0xfff, value);
}

/* Copies the canonical ISA string (NUL-terminated, truncated to `len`);
 * returns its full length. */
size_t sailrv_isa_string(void *h, char *buf, size_t len) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    sail_string s = nullptr;
    CREATE(sail_string)(&s);
    o->m.zgenerate_canonical_isa_string(&s, UNIT);
    size_t n = strlen(s);
    if (len > 0) {
        snprintf(buf, len, "%s", s);
    }
    KILL(sail_string)(&s);
    return n;
}

uint8_t sailrv_read_byte(void *h, uint64_t addr) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return (uint8_t)read_mem(addr);
}

void sailrv_write_byte(void *h, uint64_t addr, uint8_t byte) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    write_mem(addr, (uint64_t)byte);
}

bool sailrv_is_mapped(void *h, uint64_t addr) {
    OracleInstance *o = cast(h);
    Ctx ctx(o);
    return sail_addr_mapped(addr);
}

} // extern "C"
