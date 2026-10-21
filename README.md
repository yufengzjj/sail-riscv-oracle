# sail-riscv-oracle

A Rust crate that embeds the official **Sail RISC-V model**
([riscv/sail-riscv](https://github.com/riscv/sail-riscv), the golden
reference model adopted by RISC-V International) as an **in-process golden
reference CPU** for differential testing: set up architectural state, execute
one instruction at a time, and diff registers, CSRs and memory effects against
your own emulator/JIT/decoder.

## Features

- **RV32 and RV64 from one build**: sail-riscv picks XLEN (and VLEN, ELEN and
  every extension) from a JSON configuration at run time, so each `Oracle`
  chooses its own — RV32 and RV64 instances can live side by side.
- **All unprivileged extensions on by default**, including the experimental
  ones sail-riscv implements (see [Supported extensions](#supported-extensions)).
- **VLEN per instance**: default 256 bits, any power of two in 8..=65536 via
  `Oracle::builder().vlen(bits)`.
- **Two ways to step**: `step(opcode)` injects the encoding (no fetch from
  memory, any PC works); `step_fetch()` fetches from memory at PC like real
  hardware (translation, PMP/PMA and fetch faults included).
- **Per-step change list**: every step returns the register, FP, vector, CSR
  and memory writes (plus memory reads, faults, traps and xRETs) in the order
  the model performed them, so a diff does not need full-state snapshots.
- **Multi-instance, thread-safe**: every `Oracle` is a fully independent hart
  — registers, memory AND configuration are per instance. `Oracle` is
  `Send + Sync` (a process-wide mutex serializes model calls — safety, not
  parallel speedup; use `cargo nextest` processes for parallelism).
- **Self-contained & cross-platform**: the pre-generated model, a
  portability-patched Sail runtime and SoftFloat are vendored; building needs
  only Rust + C/C++ compilers (C++20). Verified on Windows 11 (MSVC) and
  Linux (musl). No Sail/OCaml/z3/GMP/zlib installation.
- **Deterministic**: no interrupts unless software raises them, clocks do not
  advance, the Zkr entropy source is a seeded PRNG.

## Design

```
sail-riscv model/riscv.sail_project  +  sail/oracle.sail_project (harness.sail)
        │  sail --cpp --c-no-main  (scripts/gen_model.sh + fix_cpp_model.py)
        ▼
  sail_riscv_model.cpp / .h   (class hart::Model — ALL architectural state is
        │                      instance members; 19 MB, vendored as 2.2 MB .gz)
        │  cc (build.rs): model + sail-riscv platform/SoftFloat glue + csrc/shim.cpp [C++20]
        │                 + patched Sail C runtime (bundled mini-gmp) + SoftFloat 3 [C]
        ▼
   sailriscv_{model,runtime,softfloat} static libs ──extern "C" sailrv_* ABI──► src/lib.rs (Oracle: Send+Sync)
```

Key decisions:

- **Sail's C++ backend** (what sail-riscv itself uses): state is class
  members, so several independent harts fit in one process. The shim derives
  from `hart::Model` and implements sail-riscv's platform callbacks
  (reservations, event counters, entropy) the way its own `c_emulator` does,
  plus change-list recording.
- **Instruction injection through RVFI-DII**: sail-riscv's fetch already has a
  path for externally supplied instructions (used by TestRIG). `step(opcode)`
  turns it on for one step and calls the model's own `try_step`, so decode,
  execute, trap entry, counters and PC update are exactly the model's.
- **Per-instance memory and configuration**: the Sail runtime keeps memory
  and the parsed JSON config in process globals, and sail-riscv reads its
  config during execution (not only at init). The shim swaps each instance's
  memory lists and config tree into the globals around every call
  (single-threaded under the lock, so this is exact).
- **Plain 64-bit ABI**: XLEN/FLEN values cross zero-extended to `u64`; vector
  registers cross as `u64` chunks. No GMP types in the interface.
- **Links next to other Sail oracles**: sail-aarch64-oracle and
  hybrid-x86-oracle carry their own Sail runtime, SoftFloat and mini-gmp with
  the same C names. Here every exported name starts with `sailrv_`: the shim
  API is named so directly, and `csrc/sailrv_prefix.h`, force-included into
  every C/C++ file, renames the rest (runtime, SoftFloat, mini-gmp, model
  globals, sail-riscv glue). SoftFloat's own `softfloat_*` names are
  rewritten in a build-time copy instead, because SoftFloat tests them with
  `#ifndef`. `tests/coexist/` links this crate with the aarch64 one in one
  test binary.

## Reset state

`Oracle::new()` (RV64) / `Oracle::rv32()` start from sail-riscv's own
`rv64d`/`rv32d` configurations with these changes:

| Item | Value |
|---|---|
| Privilege | M-mode, `satp` = Bare (no translation) |
| PC | `0x8000_0000` (`Builder::reset_pc`) |
| RAM | `[0x8000_0000, 0x1_0000_0000)` (main memory; executable) |
| ROM / MMIO | `[0x1000, 0x2000)` read-only; `[0x200_0000, 0x1200_0000)` MMIO (CLINT at `0x200_0000`) |
| VLEN / ELEN | 256 / 64 (`Builder::vlen`, `Builder::elen`) |
| `mstatus.FS` / `.VS` | Initial — FP and vector code runs without a CSR write first |
| `mtimecmp` | all ones (otherwise mtime = mtimecmp = 0 keeps a timer interrupt pending) |
| WFI, WRS.NTO, WRS.STO | retire as nops |
| Zkr entropy | PRNG seeded with 0 (`Builder::seed`) |
| Misaligned loads/stores | allowed (no fault); misaligned AMO/LR/SC → access fault |

Any other configuration item can be changed with
`Builder::set("dotted.path", "<json>")`, or replace the whole configuration
with `Builder::config_json`. `build()` returns an error if the model rejects
the configuration (it prints the reasons to stdout).

## Supported extensions

Everything sail-riscv implements. The default ISA string is:

```
rv64imafdcbvh_zic64b_zibi_zicbom_zicbop_zicboz_ziccamoa_ziccamoc_ziccif_zicclsm_ziccrse_zicfilp_zicfiss_zicntr_zicond_zicsr_zifencei_zihintntl_zihintpause_zihpm_zilx_zimop_za128rs_za64rs_zabha_zacas_zama16b_zawrs_zfa_zfbfmin_zfh_zfhmin_zca_zcb_zcd_zcmop_zbc_zbkb_zbkc_zbkx_zknd_zkne_zknh_zkr_zksed_zksh_zkt_zvabd_zvbb_zvbc_zve32f_zve32x_zve64d_zve64f_zve64x_zvfbfmin_zvfbfwma_zvfh_zvfhmin_zvkg_zvkned_zvknha_zvknhb_zvksed_zvksh_zvkt_zvl32b_..._zvl1024b_ssccptr_sscofpmf_..._sdtrig
```

(B stands for Zba/Zbb/Zbs; RV32 adds Zcf.) Zibi, Zilx and Zvabd are
experimental in sail-riscv and enabled here. `tests/extensions.rs` executes
one representative instruction per unprivileged extension (encodings from
llvm-mc) and requires each to retire without a trap.

**Zfinx/Zdinx/Zhinx** exclude F/D, so they need their own instance:
`Oracle::builder().zfinx().build()` switches FP to the integer registers and
turns off F/D and everything built on them (Zfh, Zfa, Zfbfmin, Zcf/Zcd, vector
FP — vectors stay as Zve64x).

Extensions that sail-riscv's configuration has no entry for (e.g. Zcmp/Zcmt)
are not available; see sail-riscv's README for its roadmap.

## API

| State | API |
|---|---|
| x1–x31, PC | `set_x/get_x`, `set_pc/get_pc` |
| f0–f31 (raw FLEN bits, NaN-boxed), fcsr | `set_f/get_f`, `set_fcsr/get_fcsr` |
| v0–v31 (VLEN bits as `u64` chunks) | `set_v/get_v`, `v_chunks()` |
| vl, vtype, vstart, vcsr (raw) | `set_vl/get_vl`, `set_vtype/get_vtype`, `set_vstart/get_vstart`, `set_vcsr/get_vcsr` |
| Any CSR, from M-mode | `read_csr(n) -> Option<u64>`, `write_csr(n, v) -> bool` (legalized, with side effects); constants in `csr::*` |
| Privilege (U/S/M/VU/VS) | `privilege()`, `set_privilege()` |
| Configuration | `xlen()`, `flen()`, `vlen()`, `elen()`, `has_f_regs()`, `has_v_regs()`, `isa_string()` |
| Execution | `step(opcode) -> Step`, `step_fetch() -> Step` |
| Memory (per instance, physical, byte-addressed, little-endian) | `read_mem_byte/write_mem_byte`, `read_mem/write_mem`, `read_mem_u32/u64`, `write_mem_u32/u64`, `is_mapped(addr)` |
| Snapshot | `snapshot() -> CpuState` (x, f, pc, fcsr, privilege) |

The `set_*` register setters are raw writes: they do not dirty
`mstatus.FS/VS` and do not appear in a change list. `write_csr` is the
architectural path (like a `csrw` from M-mode).

`Step { retired, changes }`: `retired` is false when the instruction trapped;
`step.trap()` gives `(interrupt, cause)`; the handler state is in the CSRs
(`mepc`, `mcause`, `mtval`, or the S/VS ones when delegated). `Change` is one of
`X`, `F`, `V`, `Csr`, `MemRead`, `MemWrite`, `MemFault`, `Trap`, `Xret`.
CSR changes include implicit writes (fflags accrual, `mstatus.FS` dirtying,
trap CSRs); on RV32 a 64-bit CSR shows up as two writes (e.g. `mstatus` and
`mstatush`).

```rust
use sail_riscv_oracle::{Change, Oracle};

let mut cpu = Oracle::builder().rv32().vlen(256).build().unwrap();
cpu.set_x(1, 5);
cpu.set_x(2, 7);
let step = cpu.step(0x0020_81B3); // add x3, x1, x2
assert_eq!(step.changes, vec![Change::X { reg: 3, value: 12 }]);
```

With proptest, a fresh `Oracle` per case is fine (about 0.8 ms each):

```rust
proptest! {
    #[test]
    fn add_matches_model(a in any::<u64>(), b in any::<u64>()) {
        let mut cpu = Oracle::new();
        cpu.set_x(1, a); cpu.set_x(2, b);
        cpu.step(0x0020_81B3);          // add x3, x1, x2
        prop_assert_eq!(cpu.get_x(3), my_model_add(a, b));
    }
}
```

## Boundaries & limitations

- **`step(opcode)` turns MMIO off**: sail-riscv's RVFI mode (which provides the
  injection) also disables its MMIO devices, so during `step` an access to the
  CLINT/HTIF range goes to plain memory (subject to the MMIO region's PMAs).
  `step_fetch()` keeps the devices.
- **Clocks do not advance**: `mcycle` and `mtime`/`time` only move in the
  model's `tick_clock`, which the oracle never calls; `minstret` counts
  retired instructions. Interrupts only happen if software
  makes them pending (e.g. writing `mip` or the CLINT through `step_fetch`).
- **Hard failures abort the process**: a configuration missing a key the model
  reads, or a model `internal_error`, ends the process (Sail runtime
  behaviour), like a panic that cannot be caught. Prefer `Builder::set` over
  hand-written full configurations.
- **Physical memory API**: `read_mem`/`write_mem` work on physical addresses
  and bypass PMA/PMP; reads of never-written addresses return 0.
- **Threading**: cross-thread use is safe but serialized by one global lock;
  parallel throughput comes from processes (`cargo nextest`), not threads.
- **Cost**: creating an instance ≈ 0.8 ms; a scalar step ≈ 11 µs; a vector
  step at VLEN = 4096 ≈ 0.3 ms (Windows 11, release build).
- **Licensing**: crate code is BSD-3-Clause; the vendored model and runtime
  are BSD-2-Clause, SoftFloat BSD-3-Clause, but bundled **mini-gmp is
  LGPLv3+/GPLv2+** — see `LICENSE` before redistributing binaries.

> ✅ Verified (2026-10, Sail 0.20.3, sail-riscv `2281e8bd`) on Windows 11
> MSVC and Linux/musl — 28 tests: single instructions on RV32/RV64
> (integer, compressed, loads/stores, LR/SC, FP incl. NaN-boxing and fflags,
> vectors at several VLENs), traps, CSR access, `step_fetch`, change lists,
> per-extension coverage, multi-instance/memory isolation and cross-thread
> use. MinGW (`x86_64-pc-windows-gnu`) has not been tried.

---

## Quick start

```sh
cargo test               # works out of the box (Oracle is Send+Sync)
cargo nextest run        # …or process-per-test for real parallelism
```

Needs only Rust and C/C++ compilers (C++20: g++ 10+/clang 10+/VS2019 16.11+).
The vendored model is unpacked into `OUT_DIR` at build time; the native code
is always built with at least `-O2` (set `SAIL_MODEL_DEBUG=1` to use the
profile's level instead).

Optional env switches (same as the aarch64 oracle):

- `SAIL_SYSTEM_GMP=1` or feature `system-gmp`/`system-gmp-static` — link a
  real libgmp instead of mini-gmp (`GMP_DIR`, `GMP_INCLUDE_DIR`/`GMP_LIB_DIR`).
- `RISCV_ORACLE_SAIL_MODEL_C` (and `_INC`) — build against a freshly
  generated `sail_riscv_model.cpp` instead of the vendored one.
- Do **not** set `SAIL_LIB_DIR` for this crate: the shim needs the patched
  vendored runtime (per-instance config swap).

## Regenerating the model (WSL2 / Linux only)

Only needed after editing `sail/harness.sail` or to track a newer sail-riscv.
Sail is OCaml-based; use WSL2 on Windows. Verified on Alpine:

```sh
# once: opam + Sail (and z3 on PATH; gmp-dev, zlib-dev for building Sail)
opam init --bare --disable-sandboxing
opam switch create 5.3.0 ocaml-base-compiler.5.3.0
opam install sail.0.20.3          # >= sail-riscv's cmake/sail_required_version.txt
git clone https://github.com/riscv/sail-riscv ~/sail-riscv

# each time
source env.sh
sh scripts/gen_model.sh ~/sail-riscv     # a few minutes
```

`gen_model.sh` runs Sail with the same flags as sail-riscv's own C++ target
(`model/CMakeLists.txt`), adds `sail/oracle.sail_project` as one more module
and a `--c-preserve` per harness function (Sail's dead-code elimination drops
anything nothing calls), applies `scripts/fix_cpp_model.py`, checks every
harness function survived, and refreshes `vendor/` (model, header,
`SAIL_RISCV_COMMIT`). Set `NO_VENDOR=1` to only generate.

When tracking a newer sail-riscv, also refresh `vendor/config/*.json` from its
`build/config/rv{32,64}d_v256_e64.json` and `vendor/riscv/` from its
`c_emulator/` (see `vendor/README.md`), then run the tests — upstream renames
show up as compile errors in `harness.sail` or `shim.cpp`.

## Regenerating the prefix header (Windows MSVC)

After any change that can add global C/C++ names (new Sail runtime, SoftFloat,
sail-riscv glue or model), refresh `csrc/sailrv_prefix.h` from Git Bash and
verify it (needs `llvm-objdump`; found on PATH, via `LLVM_OBJDUMP` or in
`C:\LLVM\bin`):

```sh
sh scripts/gen_prefix_header.sh           # builds, lists the libs' global names, writes the header
sh scripts/gen_prefix_header.sh --check   # rebuilds; fails if any global name lacks the sailrv_ prefix
cd tests/coexist && cargo test            # links with sail-aarch64-oracle (slow first build)
```
