//! End-to-end tests: drive real RISC-V instructions through the Sail model.
//!
//! Every `Oracle` is an independent hart, so tests freely create several.
//! `Oracle` is `Send + Sync` (a process-wide mutex serializes model calls), so
//! plain parallel `cargo test` is safe; `cargo nextest run` gives real
//! process-level parallelism.

use sail_riscv_oracle::{csr, Change, Oracle, Privilege};

const RAM: u64 = 0x8000_0000;

/// add x3, x1, x2
const ADD_X3_X1_X2: u32 = 0x0020_81B3;
/// addiw x3, x1, 1
const ADDIW_X3_X1_1: u32 = 0x0010_819B;
/// c.addi x1, 1
const C_ADDI_X1_1: u32 = 0x0085;
/// sd x2, 0(x1)
const SD_X2_0_X1: u32 = 0x0020_B023;
/// ld x3, 0(x1)
const LD_X3_0_X1: u32 = 0x0000_B183;
/// sw x2, 0(x1)
const SW_X2_0_X1: u32 = 0x0020_A023;
/// lw x3, 0(x1)
const LW_X3_0_X1: u32 = 0x0000_A183;
/// lr.d x3, (x1)
const LR_D_X3_X1: u32 = 0x1000_B1AF;
/// sc.d x4, x2, (x1)
const SC_D_X4_X2_X1: u32 = 0x1820_B22F;
/// fadd.d f3, f1, f2 (rm = dyn)
const FADD_D_F3_F1_F2: u32 = 0x0220_F1D3;
/// fdiv.d f3, f1, f2 (rm = dyn)
const FDIV_D_F3_F1_F2: u32 = 0x1A20_F1D3;
/// fadd.s f3, f1, f2 (rm = dyn)
const FADD_S_F3_F1_F2: u32 = 0x0020_F1D3;
/// vsetvli x5, x0, e64, m1, ta, ma  (rd != x0, rs1 = x0: vl = VLMAX)
const VSETVLI_X5_E64_M1: u32 = 0x0D80_72D7;
/// vadd.vv v3, v1, v2
const VADD_VV_V3_V1_V2: u32 = 0x0220_81D7;
/// ecall
const ECALL: u32 = 0x0000_0073;
/// wfi
const WFI: u32 = 0x1050_0073;
/// csrrw x5, seed, x0
const CSRRW_X5_SEED_X0: u32 = 0x0150_12F3;
/// csrrs x5, mstatus, x0  (csrr x5, mstatus)
const CSRR_X5_MSTATUS: u32 = 0x3000_22F3;
/// lr.w a1, (a0)
const LR_W_A1_A0: u32 = 0x1005_25AF;
/// sc.w a1, a2, (a0)
const SC_W_A1_A2_A0: u32 = 0x18C5_25AF;
/// amoadd.w a1, a2, (a0)
const AMOADD_W_A1_A2_A0: u32 = 0x00C5_25AF;
/// rdcycle a1
const RDCYCLE_A1: u32 = 0xC000_25F3;
/// rdinstret a1
const RDINSTRET_A1: u32 = 0xC020_25F3;
/// rdtime a1
const RDTIME_A1: u32 = 0xC010_25F3;
/// cbo.zero (a0)
const CBO_ZERO_A0: u32 = 0x0045_200F;
/// sw a2, 0(a0)
const SW_A2_0_A0: u32 = 0x00C5_2023;
/// lw a1, 0(a0)
const LW_A1_0_A0: u32 = 0x0005_2583;

const A0: u32 = 10;
const A1: u32 = 11;
const A2: u32 = 12;

const FFLAGS_DZ: u64 = 1 << 3;
const CAUSE_ILLEGAL_INSTR: u64 = 2;
const CAUSE_LOAD_ACCESS_FAULT: u64 = 5;
const CAUSE_STORE_ACCESS_FAULT: u64 = 7;
const CAUSE_ECALL_M: u64 = 11;

fn f64_bits(v: f64) -> u64 {
    v.to_bits()
}

#[test]
fn add_rv64() {
    let mut cpu = Oracle::new();
    assert_eq!(cpu.xlen(), 64);
    cpu.set_x(1, 5);
    cpu.set_x(2, 7);
    let pc = cpu.get_pc();
    assert_eq!(pc, RAM);
    let step = cpu.step(ADD_X3_X1_X2);
    assert!(step.retired, "{step:?}");
    assert_eq!(step.changes, vec![Change::X { reg: 3, value: 12 }]);
    assert_eq!(cpu.get_x(3), 12);
    assert_eq!(cpu.get_pc(), pc + 4);
}

#[test]
fn add_rv32_wraps_at_32_bits() {
    let mut cpu = Oracle::rv32();
    assert_eq!(cpu.xlen(), 32);
    cpu.set_x(1, 0xFFFF_FFFF);
    cpu.set_x(2, 1);
    cpu.step(ADD_X3_X1_X2);
    assert_eq!(cpu.get_x(3), 0);
    // Writes are truncated to XLEN and read back zero-extended.
    cpu.set_x(4, 0x1_2345_6789);
    assert_eq!(cpu.get_x(4), 0x2345_6789);
}

#[test]
fn x0_is_hardwired_zero() {
    let mut cpu = Oracle::new();
    cpu.set_x(0, 42);
    assert_eq!(cpu.get_x(0), 0);
}

#[test]
fn addiw_sign_extends_on_rv64() {
    let mut cpu = Oracle::new();
    cpu.set_x(1, 0x7FFF_FFFF);
    cpu.step(ADDIW_X3_X1_1);
    assert_eq!(cpu.get_x(3), 0xFFFF_FFFF_8000_0000);
}

#[test]
fn compressed_instruction_advances_pc_by_2() {
    for mut cpu in [Oracle::new(), Oracle::rv32()] {
        cpu.set_x(1, 41);
        let pc = cpu.get_pc();
        let step = cpu.step(C_ADDI_X1_1);
        assert!(step.retired);
        assert_eq!(cpu.get_x(1), 42);
        assert_eq!(cpu.get_pc(), pc + 2);
    }
}

#[test]
fn store_load_round_trip_and_change_list() {
    let mut cpu = Oracle::new();
    let addr = RAM + 0x1000;
    cpu.set_x(1, addr);
    cpu.set_x(2, 0x1122_3344_5566_7788);
    let step = cpu.step(SD_X2_0_X1);
    assert!(step.retired);
    let writes: Vec<_> = step
        .changes
        .iter()
        .filter_map(|c| match c {
            Change::MemWrite { addr, data, .. } => Some((*addr, data.clone())),
            _ => None,
        })
        .collect();
    assert_eq!(writes, vec![(addr, 0x1122_3344_5566_7788u64.to_le_bytes().to_vec())]);
    assert_eq!(cpu.read_mem_u64(addr), 0x1122_3344_5566_7788);

    let step = cpu.step(LD_X3_0_X1);
    assert_eq!(cpu.get_x(3), 0x1122_3344_5566_7788);
    assert!(step.changes.iter().any(|c| matches!(c, Change::MemRead { addr: a, .. } if *a == addr)));
}

#[test]
fn direct_memory_access_matches_instructions() {
    let mut cpu = Oracle::rv32();
    let addr = RAM + 0x2000;
    cpu.write_mem_u32(addr, 0xDEAD_BEEF);
    cpu.set_x(1, addr);
    cpu.step(LW_X3_0_X1);
    // lw sign-extends to XLEN = 32: still 0xDEADBEEF.
    assert_eq!(cpu.get_x(3), 0xDEAD_BEEF);

    cpu.set_x(2, 0x0BAD_F00D);
    cpu.step(SW_X2_0_X1);
    assert_eq!(cpu.read_mem_u32(addr), 0x0BAD_F00D);
    assert!(cpu.is_mapped(addr));
    assert!(!cpu.is_mapped(0x4000_0000_0000));
}

#[test]
fn lr_sc_succeeds() {
    let mut cpu = Oracle::new();
    let addr = RAM + 0x3000;
    cpu.write_mem_u64(addr, 5);
    cpu.set_x(1, addr);
    cpu.set_x(2, 9);
    cpu.step(LR_D_X3_X1);
    assert_eq!(cpu.get_x(3), 5);
    cpu.step(SC_D_X4_X2_X1);
    assert_eq!(cpu.get_x(4), 0, "sc.d should succeed");
    assert_eq!(cpu.read_mem_u64(addr), 9);
}

#[test]
fn set_reservation_lets_sc_succeed() {
    let mut cpu = Oracle::new();
    let addr = RAM + 0x3000;
    cpu.set_x(A0, addr);
    cpu.set_x(A2, 0x1234_5678);
    cpu.set_reservation(Some(addr));
    assert_eq!(cpu.reservation(), Some(addr));
    let step = cpu.step(SC_W_A1_A2_A0);
    assert!(step.retired, "{step:?}");
    assert_eq!(cpu.get_x(A1), 0);
    assert_eq!(cpu.read_mem_u32(addr), 0x1234_5678);
    assert_eq!(cpu.reservation(), None);
}

#[test]
fn cleared_reservation_makes_sc_fail() {
    let mut cpu = Oracle::new();
    let addr = RAM + 0x3000;
    cpu.write_mem_u32(addr, 5);
    cpu.set_x(A0, addr);
    cpu.set_x(A2, 9);
    cpu.set_reservation(Some(addr));
    cpu.set_reservation(None);
    assert_eq!(cpu.reservation(), None);
    let step = cpu.step(SC_W_A1_A2_A0);
    assert!(step.retired, "{step:?}");
    assert_eq!(step.changes, vec![Change::X { reg: A1, value: 1 }]);
    assert_eq!(cpu.read_mem_u32(addr), 5);
}

#[test]
fn lr_sets_the_reservation_and_sc_clears_it() {
    let mut cpu = Oracle::new();
    let addr = RAM + 0x3004;
    cpu.set_x(A0, addr);
    assert_eq!(cpu.reservation(), None);
    cpu.step(LR_W_A1_A0);
    assert_eq!(cpu.reservation(), Some(addr));
    cpu.step(SC_W_A1_A2_A0);
    assert_eq!(cpu.get_x(A1), 0);
    assert_eq!(cpu.reservation(), None);
}

#[test]
fn failed_sc_also_clears_the_reservation() {
    let mut cpu = Oracle::new();
    cpu.set_x(A0, RAM + 0x3000);
    cpu.set_reservation(Some(RAM + 0x4000));
    cpu.step(SC_W_A1_A2_A0);
    assert_eq!(cpu.get_x(A1), 1);
    assert_eq!(cpu.reservation(), None);
}

#[test]
fn reservation_does_not_skip_the_sc_access_check() {
    let mut cpu = Oracle::new();
    cpu.write_csr(csr::MTVEC, RAM + 0x100);
    let rom = 0x1000;
    cpu.set_x(A0, rom);
    cpu.set_reservation(Some(rom));
    let step = cpu.step(SC_W_A1_A2_A0);
    assert_eq!(step.trap(), Some((false, CAUSE_STORE_ACCESS_FAULT)));
    assert_eq!(cpu.reservation(), Some(rom));
}

fn atomic_setup(offset: u64) -> Oracle {
    let mut cpu = Oracle::new();
    cpu.write_csr(csr::MTVEC, RAM + 0x100);
    cpu.write_mem_u64(RAM + 0x1000, 0x1111_2222_3333_4444);
    cpu.write_mem_u64(RAM + 0x1008, 0x5555_6666_7777_8888);
    cpu.set_x(A0, RAM + 0x1000 + offset);
    cpu.set_x(A2, 1);
    cpu
}

#[test]
fn misaligned_amo_within_16_bytes_executes() {
    let mut cpu = atomic_setup(2);
    let step = cpu.step(AMOADD_W_A1_A2_A0);
    assert!(step.retired, "{step:?}");
    assert_eq!(cpu.get_x(A1), 0x2222_3333);
    assert_eq!(cpu.read_mem_u64(RAM + 0x1000), 0x1111_2222_3334_4444);

    let mut cpu = atomic_setup(12);
    assert!(cpu.step(AMOADD_W_A1_A2_A0).retired);
    assert_eq!(cpu.get_x(A1), 0x5555_6666);
    assert_eq!(cpu.read_mem_u64(RAM + 0x1008), 0x5555_6667_7777_8888);
}

#[test]
fn misaligned_amo_crossing_16_bytes_is_a_store_access_fault() {
    let mut cpu = atomic_setup(14);
    let step = cpu.step(AMOADD_W_A1_A2_A0);
    assert_eq!(step.trap(), Some((false, CAUSE_STORE_ACCESS_FAULT)));
    assert_eq!(cpu.read_csr(csr::MTVAL), Some(RAM + 0x100E));
    assert_eq!(cpu.read_mem_u64(RAM + 0x1008), 0x5555_6666_7777_8888);
}

#[test]
fn misaligned_lr_sc_are_access_faults() {
    let mut cpu = atomic_setup(2);
    let step = cpu.step(LR_W_A1_A0);
    assert_eq!(step.trap(), Some((false, CAUSE_LOAD_ACCESS_FAULT)));
    assert_eq!(cpu.reservation(), None);

    let mut cpu = atomic_setup(2);
    cpu.set_reservation(Some(RAM + 0x1002));
    let step = cpu.step(SC_W_A1_A2_A0);
    assert_eq!(step.trap(), Some((false, CAUSE_STORE_ACCESS_FAULT)));
    assert_eq!(cpu.read_mem_u64(RAM + 0x1000), 0x1111_2222_3333_4444);
}

#[test]
fn fadd_d() {
    let mut cpu = Oracle::new();
    assert!(cpu.has_f_regs());
    assert_eq!(cpu.flen(), 64);
    cpu.set_f(1, f64_bits(1.5));
    cpu.set_f(2, f64_bits(2.25));
    let step = cpu.step(FADD_D_F3_F1_F2);
    assert!(step.retired, "{step:?}");
    assert_eq!(f64::from_bits(cpu.get_f(3)), 3.75);
    assert!(step.changes.contains(&Change::F { reg: 3, value: f64_bits(3.75) }));
}

#[test]
fn fdiv_by_zero_sets_dz() {
    let mut cpu = Oracle::new();
    cpu.set_f(1, f64_bits(1.0));
    cpu.set_f(2, f64_bits(0.0));
    cpu.step(FDIV_D_F3_F1_F2);
    assert_eq!(f64::from_bits(cpu.get_f(3)), f64::INFINITY);
    assert_eq!(cpu.get_fcsr() & 0x1F, FFLAGS_DZ);
}

#[test]
fn single_precision_requires_nan_boxing() {
    let mut cpu = Oracle::new();
    let one = 1.0f32.to_bits() as u64;
    cpu.set_f(1, 0xFFFF_FFFF_0000_0000 | one);
    cpu.set_f(2, one); // not NaN-boxed: reads as the canonical NaN
    cpu.step(FADD_S_F3_F1_F2);
    assert_eq!(cpu.get_f(3), 0xFFFF_FFFF_7FC0_0000);

    cpu.set_f(2, 0xFFFF_FFFF_0000_0000 | one);
    cpu.step(FADD_S_F3_F1_F2);
    assert_eq!(cpu.get_f(3), 0xFFFF_FFFF_0000_0000 | 2.0f32.to_bits() as u64);
}

#[test]
fn vector_add_at_default_vlen() {
    let mut cpu = Oracle::new();
    assert!(cpu.has_v_regs());
    assert_eq!(cpu.vlen(), 256);
    let chunks = cpu.v_chunks();
    assert_eq!(chunks, 4);

    cpu.step(VSETVLI_X5_E64_M1);
    assert_eq!(cpu.get_x(5), 4, "VLMAX for e64/m1 at VLEN=256");
    assert_eq!(cpu.get_vl(), 4);

    let a: Vec<u64> = (0..chunks as u64).collect();
    let b: Vec<u64> = (0..chunks as u64).map(|i| 1000 * i).collect();
    cpu.set_v(1, &a);
    cpu.set_v(2, &b);
    let step = cpu.step(VADD_VV_V3_V1_V2);
    assert!(step.retired, "{step:?}");
    let expect: Vec<u64> = (0..chunks as u64).map(|i| 1001 * i).collect();
    assert_eq!(cpu.get_v(3), expect);
    assert!(step.changes.contains(&Change::V { reg: 3, value: expect }));
}

#[test]
fn vlen_is_selectable_per_instance() {
    for vlen in [128u32, 1024, 4096, 65536] {
        let mut cpu = Oracle::builder().vlen(vlen).build().unwrap();
        assert_eq!(cpu.vlen(), vlen);
        cpu.step(VSETVLI_X5_E64_M1);
        assert_eq!(cpu.get_x(5), (vlen / 64) as u64);
    }
    let rv32 = Oracle::builder().rv32().vlen(512).build().unwrap();
    assert_eq!((rv32.xlen(), rv32.vlen()), (32, 512));
}

#[test]
fn illegal_instruction_traps_to_mtvec() {
    let mut cpu = Oracle::new();
    let handler = RAM + 0x100;
    assert!(cpu.write_csr(csr::MTVEC, handler));
    let pc = cpu.get_pc();
    let step = cpu.step(0xFFFF_FFFF);
    assert!(!step.retired);
    assert_eq!(step.trap(), Some((false, CAUSE_ILLEGAL_INSTR)));
    assert_eq!(cpu.get_pc(), handler);
    assert_eq!(cpu.read_csr(csr::MEPC), Some(pc));
    assert_eq!(cpu.read_csr(csr::MCAUSE), Some(CAUSE_ILLEGAL_INSTR));
    assert_eq!(cpu.read_csr(csr::MTVAL), Some(0xFFFF_FFFF));
}

#[test]
fn ecall_from_m_mode() {
    let mut cpu = Oracle::rv32();
    cpu.write_csr(csr::MTVEC, RAM + 0x200);
    let step = cpu.step(ECALL);
    assert_eq!(step.trap(), Some((false, CAUSE_ECALL_M)));
    assert_eq!(cpu.get_pc(), RAM + 0x200);
}

#[test]
fn csr_access_from_user_mode_traps() {
    let mut cpu = Oracle::new();
    cpu.write_csr(csr::MTVEC, RAM + 0x100);
    cpu.set_privilege(Privilege::User);
    assert_eq!(cpu.privilege(), Privilege::User);
    let step = cpu.step(CSRR_X5_MSTATUS);
    assert_eq!(step.trap(), Some((false, CAUSE_ILLEGAL_INSTR)));
    assert_eq!(cpu.privilege(), Privilege::Machine);
}

#[test]
fn user_mode_builder_option() {
    for mut cpu in [
        Oracle::builder().user_mode().build().unwrap(),
        Oracle::builder().rv32().user_mode().build().unwrap(),
    ] {
        assert_eq!(cpu.privilege(), Privilege::User);
        for op in [RDCYCLE_A1, RDINSTRET_A1, RDTIME_A1, WFI] {
            let step = cpu.step(op);
            assert!(step.retired, "{op:#010x}: {step:?}");
        }

        let block = RAM + 0x1000;
        cpu.write_mem(block - 8, &[0xAA; 80]);
        cpu.set_x(A0, block + 8);
        let step = cpu.step(CBO_ZERO_A0);
        assert!(step.retired, "{step:?}");
        let mut mem = [0u8; 80];
        cpu.read_mem(block - 8, &mut mem);
        assert_eq!(mem[..8], [0xAA; 8]);
        assert_eq!(mem[8..72], [0; 64]);
        assert_eq!(mem[72..], [0xAA; 8]);

        cpu.set_x(A2, 0x0BAD_F00D);
        assert!(cpu.step(SW_A2_0_A0).retired);
        assert!(cpu.step(LW_A1_0_A0).retired);
        assert_eq!(cpu.get_x(A1), 0x0BAD_F00D);
        assert_eq!(cpu.privilege(), Privilege::User);
    }
}

#[test]
fn csr_read_write() {
    let mut cpu = Oracle::new();
    const MSCRATCH: u32 = 0x340;
    assert!(cpu.write_csr(MSCRATCH, 0xABCD));
    assert_eq!(cpu.read_csr(MSCRATCH), Some(0xABCD));
    assert_eq!(cpu.read_csr(0x7FF), None, "unimplemented CSR");
    assert!(!cpu.write_csr(0xC00, 1), "cycle is read-only");
    // FS/VS start as Initial so FP and vector code runs immediately.
    let mstatus = cpu.read_csr(csr::MSTATUS).unwrap();
    assert_eq!((mstatus >> 13) & 3, 1);
    assert_eq!((mstatus >> 9) & 3, 1);
}

#[test]
fn wfi_retires() {
    let mut cpu = Oracle::new();
    let pc = cpu.get_pc();
    let step = cpu.step(WFI);
    assert!(step.retired);
    assert_eq!(cpu.get_pc(), pc + 4);
}

#[test]
fn seed_csr_is_deterministic() {
    let read_seed = |seed| {
        let mut cpu = Oracle::builder().seed(seed).build().unwrap();
        cpu.step(CSRRW_X5_SEED_X0);
        cpu.get_x(5)
    };
    assert_eq!(read_seed(1), read_seed(1));
    assert_ne!(read_seed(1), read_seed(2));
}

#[test]
fn step_fetch_reads_instructions_from_memory() {
    let mut cpu = Oracle::new();
    cpu.write_mem_u32(RAM, ADD_X3_X1_X2);
    cpu.write_mem(RAM + 4, &(C_ADDI_X1_1 as u16).to_le_bytes());
    cpu.set_x(1, 1);
    cpu.set_x(2, 2);
    let step = cpu.step_fetch();
    assert!(step.retired, "{step:?}");
    assert_eq!(cpu.get_x(3), 3);
    cpu.step_fetch();
    assert_eq!(cpu.get_x(1), 2);
    assert_eq!(cpu.get_pc(), RAM + 6);
}

#[test]
fn isa_string_names_extensions() {
    let isa = Oracle::new().isa_string();
    assert!(isa.starts_with("rv64i"), "{isa}");
    // B implies Zba/Zbb/Zbs and is listed as "b".
    // Experimental ones too (zibi, zilx, zvabd): the oracle enables them.
    for ext in [
        "m", "a", "f", "d", "c", "b", "v", "zicond", "zvbb", "zfh", "zacas", "zkne", "zibi", "zilx",
        "zvabd",
    ] {
        assert!(isa.contains(ext), "{ext} missing from {isa}");
    }
    assert!(Oracle::rv32().isa_string().starts_with("rv32i"));
}

#[test]
fn zfinx_configuration() {
    let cpu = Oracle::builder().zfinx().build().unwrap();
    assert!(!cpu.has_f_regs());
    assert!(cpu.has_v_regs());
    assert!(cpu.isa_string().contains("zfinx"));
}

#[test]
fn invalid_configuration_is_an_error() {
    // Zfinx conflicts with F.
    let err = Oracle::builder().set("extensions.Zfinx.supported", "true").build();
    assert!(err.is_err());
    let err = Oracle::builder().config_json("{ not json").build();
    assert!(err.is_err());
}

/// Two instances in one process must be completely independent: interleave
/// writes and steps and check neither leaks into the other.
#[test]
fn two_oracles_are_independent() {
    let mut a = Oracle::new();
    let mut b = Oracle::rv32();
    a.set_x(1, 10);
    b.set_x(1, 20);
    a.set_x(2, 1);
    b.set_x(2, 2);
    a.step(ADD_X3_X1_X2);
    b.step(ADD_X3_X1_X2);
    assert_eq!(a.get_x(3), 11);
    assert_eq!(b.get_x(3), 22);
    assert_eq!((a.xlen(), b.xlen()), (64, 32));
    drop(a);
    b.step(ADD_X3_X1_X2);
    assert_eq!(b.get_x(3), 22);
    let c = Oracle::new();
    assert_eq!(c.get_x(3), 0);
    assert_eq!(b.vlen(), 256);
}

#[test]
fn memory_is_per_instance() {
    let mut a = Oracle::new();
    let mut b = Oracle::new();
    let addr = RAM + 0x8000;
    a.set_x(1, addr);
    a.set_x(2, 0xAAAA);
    a.step(SD_X2_0_X1);
    b.set_x(1, addr);
    b.step(LD_X3_0_X1);
    assert_eq!(b.get_x(3), 0, "b must not see a's store");
    assert!(!b.is_mapped(addr));
    assert_eq!(a.read_mem_u64(addr), 0xAAAA);
}

#[test]
fn oracles_usable_across_threads() {
    let handles: Vec<_> = (0..4u64)
        .map(|t| {
            std::thread::spawn(move || {
                let mut cpu = if t % 2 == 0 { Oracle::new() } else { Oracle::rv32() };
                for i in 0..200u64 {
                    cpu.set_x(1, i);
                    cpu.set_x(2, t);
                    cpu.step(ADD_X3_X1_X2);
                    assert_eq!(cpu.get_x(3), i + t);
                }
            })
        })
        .collect();
    for h in handles {
        h.join().unwrap();
    }
}
