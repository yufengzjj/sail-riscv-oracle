//! Safe Rust wrapper around the Sail RISC-V model (via `csrc/shim.cpp`).
//!
//! Each [`Oracle`] is an independent hart (state + memory + configuration),
//! RV32 or RV64. The underlying Sail C runtime is NOT thread-safe, so every
//! model call takes a process-wide mutex: [`Oracle`] is `Send + Sync`, but
//! threads give safety, not speedup (calls serialize) — for parallelism use
//! process-per-test (`cargo nextest`).

use std::ffi::{c_char, c_void, CStr, CString};
use std::sync::{Mutex, MutexGuard, PoisonError};

extern "C" {
    fn sailrv_new(
        json: *const c_char,
        keys: *const *const c_char,
        values: *const *const c_char,
        n_overrides: usize,
        pc_reset: u64,
        err: *mut c_char,
        err_len: usize,
    ) -> *mut c_void;
    fn sailrv_free(h: *mut c_void);
    fn sailrv_error(h: *mut c_void) -> *const c_char;
    fn sailrv_seed(h: *mut c_void, seed: u64);
    fn sailrv_step(h: *mut c_void, opcode: u32) -> u32;
    fn sailrv_step_fetch(h: *mut c_void) -> u32;
    fn sailrv_change_count(h: *mut c_void) -> usize;
    fn sailrv_change_get(
        h: *mut c_void,
        i: usize,
        kind: *mut u32,
        index: *mut u32,
        addr: *mut u64,
        value: *mut u64,
        data_len: *mut usize,
    );
    fn sailrv_change_data(h: *mut c_void, i: usize, buf: *mut u8);
    fn sailrv_change_access(h: *mut c_void, i: usize) -> *const c_char;
    fn sailrv_xlen(h: *mut c_void) -> u64;
    fn sailrv_flen(h: *mut c_void) -> u64;
    fn sailrv_vlen(h: *mut c_void) -> u64;
    fn sailrv_elen(h: *mut c_void) -> u64;
    fn sailrv_has_fregs(h: *mut c_void) -> bool;
    fn sailrv_has_vregs(h: *mut c_void) -> bool;
    fn sailrv_get_x(h: *mut c_void, n: u32) -> u64;
    fn sailrv_set_x(h: *mut c_void, n: u32, value: u64);
    fn sailrv_get_pc(h: *mut c_void) -> u64;
    fn sailrv_set_pc(h: *mut c_void, value: u64);
    fn sailrv_get_f(h: *mut c_void, n: u32) -> u64;
    fn sailrv_set_f(h: *mut c_void, n: u32, value: u64);
    fn sailrv_get_fcsr(h: *mut c_void) -> u64;
    fn sailrv_set_fcsr(h: *mut c_void, value: u64);
    fn sailrv_get_v(h: *mut c_void, n: u32, chunk: u32) -> u64;
    fn sailrv_set_v(h: *mut c_void, n: u32, chunk: u32, value: u64);
    fn sailrv_get_vl(h: *mut c_void) -> u64;
    fn sailrv_set_vl(h: *mut c_void, value: u64);
    fn sailrv_get_vtype(h: *mut c_void) -> u64;
    fn sailrv_set_vtype(h: *mut c_void, value: u64);
    fn sailrv_get_vstart(h: *mut c_void) -> u64;
    fn sailrv_set_vstart(h: *mut c_void, value: u64);
    fn sailrv_get_vcsr(h: *mut c_void) -> u64;
    fn sailrv_set_vcsr(h: *mut c_void, value: u64);
    fn sailrv_get_priv(h: *mut c_void) -> u64;
    fn sailrv_set_priv(h: *mut c_void, value: u64);
    fn sailrv_csr_readable(h: *mut c_void, csr: u32) -> bool;
    fn sailrv_read_csr(h: *mut c_void, csr: u32) -> u64;
    fn sailrv_write_csr(h: *mut c_void, csr: u32, value: u64) -> bool;
    fn sailrv_isa_string(h: *mut c_void, buf: *mut c_char, len: usize) -> usize;
    fn sailrv_read_byte(h: *mut c_void, addr: u64) -> u8;
    fn sailrv_write_byte(h: *mut c_void, addr: u64, byte: u8);
    fn sailrv_is_mapped(h: *mut c_void, addr: u64) -> bool;
}

/// sail-riscv's own RV64 configuration (`rv64d_v256_e64.json`), unmodified.
pub const RV64_CONFIG: &str = include_str!("../vendor/config/rv64.json");
/// sail-riscv's own RV32 configuration (`rv32d_v256_e64.json`), unmodified.
pub const RV32_CONFIG: &str = include_str!("../vendor/config/rv32.json");

/// VLEN of instances built without [`Builder::vlen`].
pub const DEFAULT_VLEN: u32 = 256;
/// Reset PC: the start of the default configuration's RAM region.
pub const DEFAULT_RESET_PC: u64 = 0x8000_0000;

/// Commonly needed CSR numbers.
pub mod csr {
    pub const FFLAGS: u32 = 0x001;
    pub const FRM: u32 = 0x002;
    pub const FCSR: u32 = 0x003;
    pub const VSTART: u32 = 0x008;
    pub const VXSAT: u32 = 0x009;
    pub const VXRM: u32 = 0x00A;
    pub const VCSR: u32 = 0x00F;
    pub const SEED: u32 = 0x015;
    pub const SSTATUS: u32 = 0x100;
    pub const STVEC: u32 = 0x105;
    pub const SEPC: u32 = 0x141;
    pub const SCAUSE: u32 = 0x142;
    pub const STVAL: u32 = 0x143;
    pub const SATP: u32 = 0x180;
    pub const MSTATUS: u32 = 0x300;
    pub const MISA: u32 = 0x301;
    pub const MEDELEG: u32 = 0x302;
    pub const MIDELEG: u32 = 0x303;
    pub const MTVEC: u32 = 0x305;
    pub const MENVCFG: u32 = 0x30A;
    pub const MEPC: u32 = 0x341;
    pub const MCAUSE: u32 = 0x342;
    pub const MTVAL: u32 = 0x343;
    pub const MINSTRET: u32 = 0xB02;
    pub const VL: u32 = 0xC20;
    pub const VTYPE: u32 = 0xC21;
    pub const VLENB: u32 = 0xC22;
}

// Serializes every model call across ALL instances: per-instance state is
// fine, but the Sail C runtime keeps process-global scratch (GMP temporaries;
// memory and config swapped through globals) touched on every call.
static MODEL_LOCK: Mutex<()> = Mutex::new(());

fn model_lock() -> MutexGuard<'static, ()> {
    // Guarded sections run only C/C++ (no panics), so a poisoned lock cannot
    // mean torn model state — keep going.
    MODEL_LOCK.lock().unwrap_or_else(PoisonError::into_inner)
}

/// A failure inside the model: a Sail assertion or pattern-match failure, a
/// configuration item it could not read, or an uncaught Sail exception such
/// as `internal_error`. The instance that reported it is poisoned.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ModelError {
    message: String,
}

impl ModelError {
    pub fn message(&self) -> &str {
        &self.message
    }
}

impl std::fmt::Display for ModelError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Sail model failure: {}", self.message)
    }
}

impl std::error::Error for ModelError {}

/// Builds an [`Oracle`] from one of the vendored configurations plus
/// overrides. Defaults: RV64, VLEN = [`DEFAULT_VLEN`], ELEN = 64, WFI and
/// WRS.{NTO,STO} retire as nops, reset PC = [`DEFAULT_RESET_PC`], entropy
/// seed 0.
#[derive(Debug, Clone)]
pub struct Builder {
    base: String,
    overrides: Vec<(String, String)>,
    pc_reset: u64,
    seed: u64,
}

impl Builder {
    fn new() -> Self {
        Builder {
            base: RV64_CONFIG.to_string(),
            overrides: Vec::new(),
            pc_reset: DEFAULT_RESET_PC,
            seed: 0,
        }
        .vlen(DEFAULT_VLEN)
        .set("platform.wfi_is_nop", "true")
        .set("extensions.Zawrs.nto.is_nop", "true")
        .set("extensions.Zawrs.sto.is_nop", "true")
    }

    /// Start from the vendored RV32 configuration (keeps earlier overrides).
    pub fn rv32(mut self) -> Self {
        self.base = RV32_CONFIG.to_string();
        self
    }

    /// Start from the vendored RV64 configuration (keeps earlier overrides).
    pub fn rv64(mut self) -> Self {
        self.base = RV64_CONFIG.to_string();
        self
    }

    /// Replace the base configuration with a complete sail-riscv JSON config
    /// (`//` comments allowed); overrides still apply on top. It must contain
    /// every key the model reads: `build()` fails if one read during setup is
    /// missing, and a step that reads a missing one fails with [`ModelError`].
    pub fn config_json(mut self, json: impl Into<String>) -> Self {
        self.base = json.into();
        self
    }

    /// VLEN in bits: a power of two in 8..=65536 (fixed for the instance's
    /// lifetime, like real hardware). Panics otherwise.
    pub fn vlen(self, bits: u32) -> Self {
        assert!(
            bits.is_power_of_two() && (8..=65536).contains(&bits),
            "VLEN must be a power of two in 8..=65536, got {bits}"
        );
        let exp = bits.trailing_zeros().to_string();
        self.set("extensions.V.vlen_exp", exp)
    }

    /// ELEN in bits (32 or 64); also caps the indexed-access index EEW.
    pub fn elen(self, bits: u32) -> Self {
        assert!(bits == 32 || bits == 64, "ELEN must be 32 or 64, got {bits}");
        let exp = bits.trailing_zeros().to_string();
        self.set("extensions.V.elen_exp", exp.clone())
            .set("extensions.V.max_index_eew_exp", exp)
    }

    /// Switch floating point to Zfinx/Zdinx/Zhinx (FP in the integer
    /// registers). These exclude F/D and everything built on them, so this
    /// also turns off Zfh/Zfhmin/Zfa/Zfbfmin, Zcf/Zcd, makes mstatus.FS
    /// read-only zero and keeps only the integer vector subset (Zve64x)
    /// with its FP-free extensions.
    pub fn zfinx(self) -> Self {
        let mut b = self;
        for ext in [
            "F", "D", "Zfh", "Zfhmin", "Zfa", "Zfbfmin", "Zcf", "Zcd", "Zvfh", "Zvfhmin",
            "Zvfbfmin", "Zvfbfwma",
        ] {
            b = b.set(&format!("extensions.{ext}.supported"), "false");
        }
        for ext in ["Zfinx", "Zdinx", "Zhinx", "Zhinxmin"] {
            b = b.set(&format!("extensions.{ext}.supported"), "true");
        }
        b.set("base.mstatus.fs_legal_states", "\"ExtContext_Off\"")
            .set("extensions.V.support_level", "\"Integer\"")
    }

    /// Set any configuration item: `path` is dotted (`"extensions.H.supported"`),
    /// `json` the new value as JSON text (`"true"`, `"12"`, `"\"Full\""`).
    /// Later settings of the same path win.
    pub fn set(mut self, path: &str, json: impl Into<String>) -> Self {
        self.overrides.retain(|(p, _)| p != path);
        self.overrides.push((path.to_string(), json.into()));
        self
    }

    /// PC after reset.
    pub fn reset_pc(mut self, pc: u64) -> Self {
        self.pc_reset = pc;
        self
    }

    /// Seed of the deterministic entropy source behind the Zkr `seed` CSR.
    pub fn seed(mut self, seed: u64) -> Self {
        self.seed = seed;
        self
    }

    /// Errors if the JSON is malformed, the model rejects the configuration
    /// (the model prints its reasons to stdout) or fails while reading it.
    pub fn build(self) -> Result<Oracle, String> {
        let base = CString::new(self.base).map_err(|_| "config contains a NUL byte")?;
        let mut keys = Vec::with_capacity(self.overrides.len());
        let mut values = Vec::with_capacity(self.overrides.len());
        for (k, v) in &self.overrides {
            keys.push(CString::new(k.as_str()).map_err(|_| "override path contains a NUL byte")?);
            values.push(CString::new(v.as_str()).map_err(|_| "override value contains a NUL byte")?);
        }
        let key_ptrs: Vec<*const c_char> = keys.iter().map(|k| k.as_ptr()).collect();
        let value_ptrs: Vec<*const c_char> = values.iter().map(|v| v.as_ptr()).collect();
        let mut err = [0 as c_char; 512];
        let _g = model_lock();
        let h = unsafe {
            sailrv_new(
                base.as_ptr(),
                key_ptrs.as_ptr(),
                value_ptrs.as_ptr(),
                key_ptrs.len(),
                self.pc_reset,
                err.as_mut_ptr(),
                err.len(),
            )
        };
        if h.is_null() {
            let msg = unsafe { CStr::from_ptr(err.as_ptr()) };
            return Err(msg.to_string_lossy().into_owned());
        }
        unsafe { sailrv_seed(h, self.seed) };
        Ok(Oracle { h })
    }
}

/// Privilege mode of the hart.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Privilege {
    User,
    Supervisor,
    Machine,
    /// VU-mode (H extension).
    VirtualUser,
    /// VS-mode (H extension).
    VirtualSupervisor,
}

impl Privilege {
    fn to_bits(self) -> u64 {
        match self {
            Privilege::User => 0b000,
            Privilege::Supervisor => 0b001,
            Privilege::Machine => 0b011,
            Privilege::VirtualUser => 0b100,
            Privilege::VirtualSupervisor => 0b101,
        }
    }

    fn from_bits(bits: u64) -> Self {
        match bits & 0b111 {
            0b000 => Privilege::User,
            0b001 => Privilege::Supervisor,
            0b100 => Privilege::VirtualUser,
            0b101 => Privilege::VirtualSupervisor,
            _ => Privilege::Machine,
        }
    }
}

/// One architectural effect recorded during a step, in the order the model
/// performed it. Register values are zero-extended to 64 bits.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Change {
    /// Integer register write (writes to x0 are not reported).
    X { reg: u32, value: u64 },
    /// FP register write (raw FLEN bits, NaN-boxed).
    F { reg: u32, value: u64 },
    /// Vector register write, 64-bit chunks (chunk 0 = bits 63..0).
    V { reg: u32, value: Vec<u64> },
    /// CSR write as reported by the model (including implicit ones such as
    /// mstatus.FS dirtying, fflags accrual, trap CSRs). On RV32 a 64-bit
    /// CSR appears as two writes (e.g. mstatus and mstatush).
    Csr { csr: u32, value: u64 },
    /// Physical-memory read; `access` is the model's access-type name.
    MemRead { addr: u64, data: Vec<u8>, access: String },
    /// Physical-memory write.
    MemWrite { addr: u64, data: Vec<u8>, access: String },
    /// Memory access fault at a physical address, with the exception number.
    MemFault { addr: u64, cause: u64 },
    /// Trap taken (exception or interrupt) with its cause code.
    Trap { interrupt: bool, cause: u64 },
    /// MRET (`mret = true`) or SRET (`mret = false`).
    Xret { mret: bool },
}

/// Result of one step: whether the instruction retired, plus every recorded
/// effect. A trapping instruction does not retire.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Step {
    pub retired: bool,
    pub changes: Vec<Change>,
}

impl Step {
    /// The trap taken during the step, if any.
    pub fn trap(&self) -> Option<(bool, u64)> {
        self.changes.iter().find_map(|c| match c {
            Change::Trap { interrupt, cause } => Some((*interrupt, *cause)),
            _ => None,
        })
    }
}

/// One hart. After a [`ModelError`] the instance is poisoned (its state is
/// undefined): every later method call panics, and dropping it is still
/// safe.
pub struct Oracle {
    h: *mut c_void,
}

// SAFETY: instance state is reachable only through this struct (&/&mut
// aliasing) and every FFI call runs under MODEL_LOCK.
unsafe impl Send for Oracle {}
unsafe impl Sync for Oracle {}

/// Must be called with MODEL_LOCK held.
unsafe fn error_of(h: *mut c_void) -> Option<String> {
    let p = sailrv_error(h);
    (!p.is_null()).then(|| CStr::from_ptr(p).to_string_lossy().into_owned())
}

impl Oracle {
    /// RV64 with the default [`Builder`] settings.
    pub fn new() -> Self {
        Self::builder().build().expect("default RV64 configuration")
    }

    /// RV32 with the default [`Builder`] settings.
    pub fn rv32() -> Self {
        Self::builder().rv32().build().expect("default RV32 configuration")
    }

    pub fn builder() -> Builder {
        Builder::new()
    }

    /// Whether an earlier call failed inside the model (see [`ModelError`]).
    pub fn is_poisoned(&self) -> bool {
        let _g = model_lock();
        unsafe { error_of(self.h) }.is_some()
    }

    /// Runs `f` with the handle under MODEL_LOCK; Err if the model failed
    /// during `f`. Panics (after releasing the lock) if the instance was
    /// already poisoned.
    fn try_call<R>(&self, f: impl FnOnce(*mut c_void) -> R) -> Result<R, ModelError> {
        let guard = model_lock();
        if let Some(message) = unsafe { error_of(self.h) } {
            drop(guard);
            panic!("Oracle used after a Sail model failure poisoned it: {message}");
        }
        let r = f(self.h);
        let failure = unsafe { error_of(self.h) };
        drop(guard);
        match failure {
            None => Ok(r),
            Some(message) => Err(ModelError { message }),
        }
    }

    fn call<R>(&self, f: impl FnOnce(*mut c_void) -> R) -> R {
        self.try_call(f).unwrap_or_else(|e| panic!("{e}"))
    }

    pub fn xlen(&self) -> u32 {
        self.call(|h| unsafe { sailrv_xlen(h) as u32 })
    }

    /// FLEN (64 with D, 32 with F only); meaningless without F.
    pub fn flen(&self) -> u32 {
        self.call(|h| unsafe { sailrv_flen(h) as u32 })
    }

    pub fn vlen(&self) -> u32 {
        self.call(|h| unsafe { sailrv_vlen(h) as u32 })
    }

    pub fn elen(&self) -> u32 {
        self.call(|h| unsafe { sailrv_elen(h) as u32 })
    }

    /// Whether the F registers exist (false for Zfinx configurations).
    pub fn has_f_regs(&self) -> bool {
        self.call(|h| unsafe { sailrv_has_fregs(h) })
    }

    /// Whether the vector registers exist (any Zve* / V support).
    pub fn has_v_regs(&self) -> bool {
        self.call(|h| unsafe { sailrv_has_vregs(h) })
    }

    /// Canonical ISA string of the configured hart, e.g. `rv64imafdcv_...`.
    pub fn isa_string(&self) -> String {
        self.call(|h| {
            let n = unsafe { sailrv_isa_string(h, std::ptr::null_mut(), 0) };
            let mut buf = vec![0 as c_char; n + 1];
            unsafe { sailrv_isa_string(h, buf.as_mut_ptr(), buf.len()) };
            unsafe { CStr::from_ptr(buf.as_ptr()) }.to_string_lossy().into_owned()
        })
    }

    /// x0 reads as zero and ignores writes. On RV32 values are truncated to
    /// 32 bits and read back zero-extended.
    pub fn set_x(&mut self, n: u32, value: u64) {
        debug_assert!(n <= 31);
        self.call(|h| unsafe { sailrv_set_x(h, n, value) })
    }

    pub fn get_x(&self, n: u32) -> u64 {
        debug_assert!(n <= 31);
        self.call(|h| unsafe { sailrv_get_x(h, n) })
    }

    pub fn set_pc(&mut self, value: u64) {
        self.call(|h| unsafe { sailrv_set_pc(h, value) })
    }

    pub fn get_pc(&self) -> u64 {
        self.call(|h| unsafe { sailrv_get_pc(h) })
    }

    /// Raw FLEN-bit contents; a single-precision value must be NaN-boxed
    /// (upper 32 bits all ones) to be read as such. Does not touch
    /// mstatus.FS. No-op without F registers.
    pub fn set_f(&mut self, n: u32, value: u64) {
        debug_assert!(n <= 31);
        self.call(|h| unsafe { sailrv_set_f(h, n, value) })
    }

    pub fn get_f(&self, n: u32) -> u64 {
        debug_assert!(n <= 31);
        self.call(|h| unsafe { sailrv_get_f(h, n) })
    }

    /// fcsr = frm[7:5] @ fflags[4:0]. Raw write: does not touch mstatus.FS.
    pub fn set_fcsr(&mut self, value: u64) {
        self.call(|h| unsafe { sailrv_set_fcsr(h, value) })
    }

    pub fn get_fcsr(&self) -> u64 {
        self.call(|h| unsafe { sailrv_get_fcsr(h) })
    }

    /// Number of 64-bit chunks in a vector register (VLEN/64, at least 1).
    pub fn v_chunks(&self) -> usize {
        (self.vlen() as usize / 64).max(1)
    }

    /// Little-endian chunks (`data[0]` = bits 63..0); missing chunks zeroed.
    /// Does not touch mstatus.VS.
    pub fn set_v(&mut self, n: u32, data: &[u64]) {
        debug_assert!(n <= 31);
        let chunks = self.v_chunks();
        debug_assert!(data.len() <= chunks);
        self.call(|h| {
            for i in 0..chunks {
                let v = data.get(i).copied().unwrap_or(0);
                unsafe { sailrv_set_v(h, n, i as u32, v) }
            }
        })
    }

    pub fn get_v(&self, n: u32) -> Vec<u64> {
        debug_assert!(n <= 31);
        let chunks = self.v_chunks();
        self.call(|h| (0..chunks).map(|i| unsafe { sailrv_get_v(h, n, i as u32) }).collect())
    }

    // Raw vector CSR state (no legality checks, no side effects). Use
    // `step` with vsetvli/vsetvl for architectural updates.

    pub fn set_vl(&mut self, value: u64) {
        self.call(|h| unsafe { sailrv_set_vl(h, value) })
    }

    pub fn get_vl(&self) -> u64 {
        self.call(|h| unsafe { sailrv_get_vl(h) })
    }

    /// vtype = vill[XLEN-1] .. vma[7] vta[6] vsew[5:3] vlmul[2:0].
    pub fn set_vtype(&mut self, value: u64) {
        self.call(|h| unsafe { sailrv_set_vtype(h, value) })
    }

    pub fn get_vtype(&self) -> u64 {
        self.call(|h| unsafe { sailrv_get_vtype(h) })
    }

    pub fn set_vstart(&mut self, value: u64) {
        self.call(|h| unsafe { sailrv_set_vstart(h, value) })
    }

    pub fn get_vstart(&self) -> u64 {
        self.call(|h| unsafe { sailrv_get_vstart(h) })
    }

    /// vcsr = vxrm[2:1] @ vxsat[0].
    pub fn set_vcsr(&mut self, value: u64) {
        self.call(|h| unsafe { sailrv_set_vcsr(h, value) })
    }

    pub fn get_vcsr(&self) -> u64 {
        self.call(|h| unsafe { sailrv_get_vcsr(h) })
    }

    pub fn privilege(&self) -> Privilege {
        Privilege::from_bits(self.call(|h| unsafe { sailrv_get_priv(h) }))
    }

    /// Raw mode switch (no xRET side effects). Virtual modes are ignored
    /// unless the H extension is configured.
    pub fn set_privilege(&mut self, p: Privilege) {
        self.call(|h| unsafe { sailrv_set_priv(h, p.to_bits()) })
    }

    /// CSR value as seen from M-mode, or None if the CSR is not accessible in
    /// this configuration/state (e.g. fcsr while mstatus.FS = Off).
    pub fn read_csr(&self, csr: u32) -> Option<u64> {
        self.call(|h| unsafe {
            if sailrv_csr_readable(h, csr) {
                Some(sailrv_read_csr(h, csr))
            } else {
                None
            }
        })
    }

    /// Architectural CSR write from M-mode: legalized, with side effects.
    /// false if the CSR does not exist, is read-only, or rejected the write.
    pub fn write_csr(&mut self, csr: u32, value: u64) -> bool {
        self.call(|h| unsafe { sailrv_write_csr(h, csr, value) })
    }

    /// Execute one instruction given by its encoding (16-bit compressed if
    /// the low two bits are not `0b11`, else 32-bit) at the current PC,
    /// without fetching from memory. Interrupt/trigger checks, decode,
    /// execute, trap entry and PC update follow the model's own step.
    /// Panics on a [`ModelError`]; see [`Oracle::try_step`].
    pub fn step(&mut self, opcode: u32) -> Step {
        self.try_step(opcode).unwrap_or_else(|e| panic!("{e}"))
    }

    /// Execute one instruction fetched from memory at the current PC
    /// (address translation, PMP/PMA and fetch faults included).
    /// Panics on a [`ModelError`]; see [`Oracle::try_step_fetch`].
    pub fn step_fetch(&mut self) -> Step {
        self.try_step_fetch().unwrap_or_else(|e| panic!("{e}"))
    }

    /// [`Oracle::step`], but a failure inside the model is returned as an
    /// error. The instance is then poisoned: drop it and build a new one.
    pub fn try_step(&mut self, opcode: u32) -> Result<Step, ModelError> {
        self.try_call(|h| {
            let flags = unsafe { sailrv_step(h, opcode) };
            collect_step(h, flags)
        })
    }

    /// [`Oracle::step_fetch`], but a failure inside the model is returned as
    /// an error. The instance is then poisoned: drop it and build a new one.
    pub fn try_step_fetch(&mut self) -> Result<Step, ModelError> {
        self.try_call(|h| {
            let flags = unsafe { sailrv_step_fetch(h) };
            collect_step(h, flags)
        })
    }

    // Direct byte-addressed, little-endian access to this instance's physical
    // memory — the same bytes the model's loads/stores see, bypassing PMA/PMP
    // checks. Unmapped addresses read as zero; writing a fresh page allocates
    // it.

    /// 0 if the address was never written.
    pub fn read_mem_byte(&self, addr: u64) -> u8 {
        self.call(|h| unsafe { sailrv_read_byte(h, addr) })
    }

    pub fn write_mem_byte(&mut self, addr: u64, byte: u8) {
        self.call(|h| unsafe { sailrv_write_byte(h, addr, byte) })
    }

    pub fn read_mem(&self, addr: u64, buf: &mut [u8]) {
        self.call(|h| {
            for (i, slot) in buf.iter_mut().enumerate() {
                *slot = unsafe { sailrv_read_byte(h, addr.wrapping_add(i as u64)) };
            }
        })
    }

    pub fn write_mem(&mut self, addr: u64, data: &[u8]) {
        self.call(|h| {
            for (i, &byte) in data.iter().enumerate() {
                unsafe { sailrv_write_byte(h, addr.wrapping_add(i as u64), byte) }
            }
        })
    }

    pub fn read_mem_u64(&self, addr: u64) -> u64 {
        let mut b = [0u8; 8];
        self.read_mem(addr, &mut b);
        u64::from_le_bytes(b)
    }

    pub fn write_mem_u64(&mut self, addr: u64, value: u64) {
        self.write_mem(addr, &value.to_le_bytes());
    }

    pub fn read_mem_u32(&self, addr: u64) -> u32 {
        let mut b = [0u8; 4];
        self.read_mem(addr, &mut b);
        u32::from_le_bytes(b)
    }

    pub fn write_mem_u32(&mut self, addr: u64, value: u32) {
        self.write_mem(addr, &value.to_le_bytes());
    }

    /// Whether `addr`'s region was ever written — the only way to tell "wrote 0"
    /// from "never touched" (reads return 0 either way). Granularity is the
    /// runtime's 16 MiB block, so one write maps its whole containing block.
    pub fn is_mapped(&self, addr: u64) -> bool {
        self.call(|h| unsafe { sailrv_is_mapped(h, addr) })
    }

    /// Integer/FP/PC/fcsr/privilege state (no vector registers).
    pub fn snapshot(&self) -> CpuState {
        let mut x = [0u64; 32];
        let mut f = [0u64; 32];
        for i in 0..32 {
            x[i] = self.get_x(i as u32);
            f[i] = self.get_f(i as u32);
        }
        CpuState { x, f, pc: self.get_pc(), fcsr: self.get_fcsr(), privilege: self.privilege() }
    }
}

/// Must be called with MODEL_LOCK held.
fn collect_step(h: *mut c_void, flags: u32) -> Step {
    let n = unsafe { sailrv_change_count(h) };
    let mut changes = Vec::with_capacity(n);
    for i in 0..n {
        let (mut kind, mut index, mut addr, mut value, mut len) = (0u32, 0u32, 0u64, 0u64, 0usize);
        unsafe { sailrv_change_get(h, i, &mut kind, &mut index, &mut addr, &mut value, &mut len) };
        let mut data = vec![0u8; len];
        if len > 0 {
            unsafe { sailrv_change_data(h, i, data.as_mut_ptr()) };
        }
        let access = || {
            unsafe { CStr::from_ptr(sailrv_change_access(h, i)) }
                .to_string_lossy()
                .into_owned()
        };
        changes.push(match kind {
            1 => Change::X { reg: index, value },
            2 => Change::F { reg: index, value },
            3 => Change::V { reg: index, value: bytes_to_chunks(&data) },
            4 => Change::Csr { csr: index, value },
            5 => Change::MemRead { addr, data, access: access() },
            6 => Change::MemWrite { addr, data, access: access() },
            7 => Change::MemFault { addr, cause: value },
            8 => Change::Trap { interrupt: index != 0, cause: value },
            9 => Change::Xret { mret: index != 0 },
            _ => unreachable!("unknown change kind {kind}"),
        });
    }
    Step { retired: flags & 1 != 0, changes }
}

fn bytes_to_chunks(data: &[u8]) -> Vec<u64> {
    data.chunks(8)
        .map(|c| {
            let mut b = [0u8; 8];
            b[..c.len()].copy_from_slice(c);
            u64::from_le_bytes(b)
        })
        .collect()
}

impl Default for Oracle {
    fn default() -> Self {
        Self::new()
    }
}

impl Drop for Oracle {
    fn drop(&mut self) {
        let _g = model_lock();
        unsafe { sailrv_free(self.h) }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct CpuState {
    pub x: [u64; 32],
    pub f: [u64; 32],
    pub pc: u64,
    pub fcsr: u64,
    pub privilege: Privilege,
}
