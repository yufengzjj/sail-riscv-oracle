/* =============================================================================
 * harness.sail — C-callable wrappers for the oracle (module `oracle` in
 * oracle.sail_project, compiled on top of the full sail-riscv model; see
 * scripts/gen_model.sh).
 *
 *   - Every wrapper needs `--c-preserve <name>`, or Sail's dead-code
 *     elimination drops it (nothing in the model calls these).
 *   - The ABI uses only fixed-width bitvectors <= 64 b, so C++ sees plain
 *     uint64_t/bool/unit. XLEN/FLEN-sized values cross zero-extended to 64 b.
 *   - Name mangling: `z` prefix, a literal `z` escapes to `zz`.
 * ===========================================================================*/

/* mstatus.FS/VS = Initial so FP/vector instructions run without a prior CSR
 * write. Goes through the legalizing CSR write, so it is a no-op when F/V
 * are absent (e.g. Zfinx configs).
 * mtimecmp = all ones: it resets to 0 like mtime, which would leave the
 * machine timer interrupt pending (an mip write in every step's changes). */
function oracle_init() -> unit = {
  let ms = read_CSR(0x300);
  let _ : result(xlenbits, unit) = write_CSR(0x300, ms | zero_extend(0x2200));
  let _ : MemoryOpResult(bool) = mmio_write(Physaddr(plat_clint_base + MTIMECMP_BASE), 8, ones());
  ()
}

function oracle_xlen() -> bits(64) = to_bits(64, xlen)

function oracle_flen() -> bits(64) = to_bits(64, flen)

function oracle_vlen() -> bits(64) = to_bits(64, vlen)

function oracle_elen() -> bits(64) = to_bits(64, 2 ^ elen_exp)

function oracle_has_fregs() -> bool = hartSupports(Ext_F)

function oracle_has_vregs() -> bool = hartSupports(Ext_Zve32x)

/* With RV32E/RV64E, x16..x31 do not exist: reads give 0, writes are dropped. */
function oracle_get_x(n : bits(5)) -> bits(64) =
  if base_E_enabled & n[4] == 0b1 then zeros()
  else zero_extend(rX_bits(Regidx(n[regidx_bit_width - 1 .. 0])))

function oracle_set_x(n : bits(5), value : bits(64)) -> unit =
  if base_E_enabled & n[4] == 0b1 then ()
  else wX_bits(Regidx(n[regidx_bit_width - 1 .. 0]), value[xlen - 1 .. 0])

function oracle_get_pc() -> bits(64) = zero_extend(PC)

function oracle_set_pc(value : bits(64)) -> unit = {
  PC = value[xlen - 1 .. 0];
  nextPC = PC
}

/* Raw FLEN-bit register contents (NaN-boxing visible). The setter restores
 * mstatus so that seeding state does not mark FS dirty. */
function oracle_get_f(n : bits(5)) -> bits(64) =
  if hartSupports(Ext_F) then zero_extend(rF_bits(Fregidx(n))) else zeros()

function oracle_set_f(n : bits(5), value : bits(64)) -> unit =
  if hartSupports(Ext_F) then {
    let saved = mstatus;
    wF_bits(Fregidx(n), value[flen - 1 .. 0]);
    mstatus = saved
  }

function oracle_get_fcsr() -> bits(64) = zero_extend(fcsr.bits)

function oracle_set_fcsr(value : bits(64)) -> unit = {
  fcsr = Mk_Fcsr(value[31 .. 0])
}

/* Vector registers in 64-bit chunks, chunk 0 = bits 63..0. Chunks past VLEN
 * read as 0 and ignore writes; for VLEN < 64 chunk 0 holds the whole
 * register. The setter restores mstatus (no VS dirtying). */
function oracle_get_v_chunk(n : bits(5), idx : bits(16)) -> bits(64) = {
  let v = rV_bits(Vregidx(n));
  let i = unsigned(idx);
  if vlen < 64 then {
    if i == 0 then zero_extend(v) else zeros()
  } else if 64 * i + 64 <= vlen then slice(v, 64 * i, 64)
  else zeros()
}

function oracle_set_v_chunk(n : bits(5), idx : bits(16), value : bits(64)) -> unit = {
  var v = rV_bits(Vregidx(n));
  let i = unsigned(idx);
  if vlen < 64 then {
    if i == 0 then v = value[vlen - 1 .. 0]
  } else if 64 * i + 64 <= vlen then {
    v[64 * i + 63 .. 64 * i] = value
  };
  let saved = mstatus;
  wV_bits(Vregidx(n), v);
  mstatus = saved
}

function oracle_get_vl() -> bits(64) = zero_extend(vl)

function oracle_set_vl(value : bits(64)) -> unit = {
  vl = value[vlen_exp .. 0]
}

function oracle_get_vtype() -> bits(64) = zero_extend(vtype.bits)

function oracle_set_vtype(value : bits(64)) -> unit = {
  vtype = Mk_Vtype(value[xlen - 1 .. 0])
}

function oracle_get_vstart() -> bits(64) = zero_extend(vstart)

function oracle_set_vstart(value : bits(64)) -> unit = {
  vstart = value[vlen_exp - 1 .. 0]
}

/* vcsr = vxrm[2:1] @ vxsat[0] */
function oracle_get_vcsr() -> bits(64) = zero_extend(vcsr.bits)

function oracle_set_vcsr(value : bits(64)) -> unit = {
  vcsr = Mk_Vcsr(value[2 .. 0])
}

/* Packed as bit2 = virtualization mode (V), bits1..0 = nominal privilege
 * (0 U, 1 S, 3 M). Encodings that name no privilege level are ignored. */
function oracle_get_priv() -> bits(8) =
  zero_extend(privLevel_to_virt_bit(cur_privilege) @ privLevel_to_bits(cur_privilege))

function oracle_set_priv(p : bits(8)) -> unit =
  match p[2 .. 0] {
    0b000 => cur_privilege = User,
    0b001 => cur_privilege = Supervisor,
    0b011 => cur_privilege = Machine,
    0b100 => if hartSupports(Ext_H) then cur_privilege = VirtualUser,
    0b101 => if hartSupports(Ext_H) then cur_privilege = VirtualSupervisor,
    _     => (),
  }

/* CSR access as seen from M-mode, through the model's own read/write clauses
 * (writes are legalized and have their architectural side effects).
 * Accessibility follows the current hart configuration (e.g. fcsr needs
 * mstatus.FS != Off). */
function oracle_csr_readable(csr : bits(12)) -> bool =
  is_CSR_accessible(csr, Machine, CSRRead)

function oracle_read_csr(csr : bits(12)) -> bits(64) =
  if is_CSR_accessible(csr, Machine, CSRRead) then zero_extend(read_CSR(csr)) else zeros()

/* false: no such CSR, read-only, or the write was rejected. */
function oracle_write_csr(csr : bits(12), value : bits(64)) -> bool =
  if check_CSR_access(csr, CSRWrite) & is_CSR_accessible(csr, Machine, CSRWrite) then {
    match write_CSR(csr, value[xlen - 1 .. 0]) {
      Ok(_)  => true,
      Err(_) => false,
    }
  } else false
