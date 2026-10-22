//! Vector rules the model patches in `sail/patches/` cover: mask
//! destinations against wider source groups, the `.vs` scalar element group
//! of the vector crypto instructions, out-of-range EMUL in unit-stride and
//! strided accesses and in vfwmaccbf16.vf, viota.m overlap, no 64-bit index
//! EEW on RV32, vs2 against vd in widening FP multiply-add .vf, the vsha2
//! element group size, and the vrgatherei16.vv index EMUL.

use sail_riscv_oracle::Oracle;

const CAUSE_ILLEGAL_INSTR: u64 = 2;
const A0: u32 = 10;
const A2: u32 = 12;
const RAM: u64 = 0x8000_0000;

/// vtype for the given SEW (8..=64) and vlmul field, tail/mask undisturbed.
fn vt(sew: u64, vlmul: u64) -> u64 {
    (sew.trailing_zeros() as u64 - 3) << 3 | vlmul
}
fn e32(vlmul: u64) -> u64 {
    vt(32, vlmul)
}
const M1: u64 = 0b000;
const M2: u64 = 0b001;
const M4: u64 = 0b010;
const M8: u64 = 0b011;
const MF2: u64 = 0b111;

fn cpu(vlen: u32, vtype: u64, vl: u64) -> Oracle {
    let mut b = Oracle::builder().vlen(vlen);
    if vlen < 128 {
        // Full V needs VLEN >= 128; Zve64d does not.
        b = b.set("extensions.V.support_level", "\"Float_double\"");
    }
    with_v(b.build().unwrap(), vtype, vl)
}

fn with_v(mut cpu: Oracle, vtype: u64, vl: u64) -> Oracle {
    cpu.set_vtype(vtype);
    cpu.set_vl(vl);
    cpu
}

/// Runs each `(asm, opcode)` on a fresh hart and checks that it retires
/// (`legal`) or raises an illegal-instruction trap.
fn check(vlen: u32, vtype: u64, vl: u64, legal: bool, cases: &[(&str, u32)]) {
    check_on(|| cpu(vlen, vtype, vl), legal, cases)
}

fn check_on(make: impl Fn() -> Oracle, legal: bool, cases: &[(&str, u32)]) {
    let mut failures = Vec::new();
    for &(asm, opcode) in cases {
        let mut cpu = make();
        cpu.set_x(A0, RAM + 0x1000);
        cpu.set_x(A2, 16);
        let step = cpu.try_step(opcode).unwrap_or_else(|e| panic!("{asm}: {e}"));
        let ok = if legal {
            step.retired && step.trap().is_none()
        } else {
            step.trap() == Some((false, CAUSE_ILLEGAL_INSTR))
        };
        if !ok {
            failures.push(format!("{asm} ({opcode:#010x}): retired {} trap {:?}", step.retired, step.trap()));
        }
    }
    let want = if legal { "retire" } else { "trap" };
    assert!(failures.is_empty(), "expected to {want}:\n{}", failures.join("\n"));
}

#[test]
fn mask_destination_in_upper_part_of_source_group_is_reserved() {
    check(128, e32(M2), 8, false, &[
        ("vmseq.vv v3, v2, v4", 0x6222_01D7),
        ("vmseq.vv v5, v2, v4", 0x6222_02D7),
        ("vmseq.vx v3, v2, a0", 0x6225_41D7),
        ("vmseq.vi v3, v2, 1", 0x6220_B1D7),
        ("vmadc.vv v3, v2, v4", 0x4622_01D7),
        ("vmadc.vvm v3, v2, v4, v0", 0x4422_01D7),
        ("vmadc.vi v3, v2, 1", 0x4620_B1D7),
        ("vmsbc.vx v3, v2, a0", 0x4E25_41D7),
        ("vmfeq.vv v3, v2, v4", 0x6222_11D7),
        ("vmfeq.vf v3, v2, fa0", 0x6225_51D7),
    ]);
}

#[test]
fn mask_destination_in_lowest_register_or_outside_is_legal() {
    check(128, e32(M2), 8, true, &[
        ("vmseq.vv v2, v2, v4", 0x6222_0157),
        ("vmseq.vv v1, v2, v4", 0x6222_00D7),
    ]);
    // With fractional LMUL every group is one register, so vd = vs2 is the
    // lowest-numbered part and v3 does not overlap v2.
    check(128, e32(MF2), 2, true, &[
        ("vmseq.vv v2, v2, v4", 0x6222_0157),
        ("vmseq.vv v3, v2, v4", 0x6222_01D7),
        ("vmfeq.vv v3, v2, v4", 0x6222_11D7),
    ]);
}

#[test]
fn vs_scalar_element_group_need_not_be_lmul_aligned() {
    check(128, e32(M2), 8, true, &[
        ("vaesz.vs v4, v3", 0xA633_A277),
        ("vaesz.vs v4, v2", 0xA623_A277),
        ("vaesef.vs v4, v3", 0xA631_A277),
        ("vsm4r.vs v4, v31", 0xA7F8_2277),
    ]);
    check(128, e32(M2), 8, false, &[
        ("vaesz.vs v4, v5", 0xA653_A277),
        ("vaesef.vv v4, v3 (.vv stays LMUL-aligned)", 0xA231_A277),
    ]);
    check(128, e32(M4), 16, false, &[("vaesdf.vs v8, v9", 0xA690_A477)]);
}

#[test]
fn vs_scalar_element_group_spans_registers_below_vlen_128() {
    // VLEN = 64: the 128-bit group is v2-v3, aligned to 2 and disjoint from vd.
    check(64, e32(M2), 4, true, &[("vaesz.vs v4, v2", 0xA623_A277)]);
    check(64, e32(M2), 4, false, &[
        ("vaesz.vs v4, v3", 0xA633_A277),
        ("vaesz.vs v4, v5", 0xA653_A277),
    ]);
}

#[test]
fn vaesz_vs_xors_the_scalar_element_group_into_every_group() {
    let mut cpu = cpu(128, e32(M2), 8);
    let key = [0x0706_0504_0302_0100, 0x0F0E_0D0C_0B0A_0908];
    let a = [0x1111_1111_2222_2222, 0x3333_3333_4444_4444];
    let b = [0x5555_5555_6666_6666, 0x7777_7777_8888_8888];
    cpu.set_v(3, &key);
    cpu.set_v(4, &a);
    cpu.set_v(5, &b);
    let step = cpu.step(0xA633_A277); // vaesz.vs v4, v3
    assert!(step.retired, "{step:?}");
    assert_eq!(cpu.get_v(4), [a[0] ^ key[0], a[1] ^ key[1]]);
    assert_eq!(cpu.get_v(5), [b[0] ^ key[0], b[1] ^ key[1]]);
}

#[test]
fn vv_and_vs_forms_agree_when_every_vs2_group_holds_the_key() {
    let key = [0x2B7E_1516_28AE_D2A6, 0xABF7_1588_09CF_4F3C];
    let state = [[0x3243_F6A8_885A_308D, 0x3131_98A2_E037_0734], [0x0011_2233_4455_6677, 0x8899_AABB_CCDD_EEFF]];
    for (name, vv, vs) in [
        ("vaesef", 0xA221_A277, 0xA661_A277), // vaesef.vv v4, v2 / vaesef.vs v4, v6
        ("vsm4r", 0xA228_2277, 0xA668_2277),  // vsm4r.vv v4, v2 / vsm4r.vs v4, v6
    ] {
        let run = |opcode: u32| {
            let mut cpu = cpu(128, e32(M2), 8);
            cpu.set_v(2, &key);
            cpu.set_v(3, &key);
            cpu.set_v(6, &key);
            cpu.set_v(4, &state[0]);
            cpu.set_v(5, &state[1]);
            let step = cpu.step(opcode);
            assert!(step.retired, "{name}: {step:?}");
            (cpu.get_v(4), cpu.get_v(5))
        };
        let out = run(vv);
        assert_ne!(out, (state[0].to_vec(), state[1].to_vec()), "{name} changed nothing");
        assert_eq!(out, run(vs), "{name}: .vv and .vs differ");
    }
}

#[test]
fn unit_stride_and_strided_emul_above_8_is_reserved() {
    // e8, m2: EEW 64 gives EMUL = 16.
    check(128, vt(8, M2), 4, false, &[
        ("vle64.v v8, (a0)", 0x0205_7407),
        ("vle64ff.v v8, (a0)", 0x0305_7407),
        ("vse64.v v8, (a0)", 0x0205_7427),
        ("vlse64.v v8, (a0), a2", 0x0AC5_7407),
        ("vsse64.v v8, (a0), a2", 0x0AC5_7427),
        ("vlseg2e64.v v8, (a0)", 0x2205_7407),
    ]);
    check(128, vt(8, M2), 4, true, &[("vle8.v v8, (a0)", 0x0205_0407)]);
    check(128, vt(8, M1), 4, true, &[("vle64.v v8, (a0)", 0x0205_7407)]);
}

#[test]
fn viota_vs2_inside_the_vd_group_is_reserved() {
    check(128, e32(M2), 4, false, &[("viota.m v2, v3", 0x5238_2157)]);
    check(128, vt(8, M8), 16, false, &[("viota.m v8, v13", 0x52D8_2457)]);
    check(128, e32(M2), 4, true, &[("viota.m v4, v3", 0x5238_2257)]);
}

#[test]
fn no_64_bit_index_eew_on_rv32() {
    let rv32 = || with_v(Oracle::builder().rv32().vlen(128).build().unwrap(), e32(M1), 2);
    check_on(rv32, false, &[
        ("vluxei64.v v4, (a0), v2", 0x0625_7207),
        ("vsuxei64.v v4, (a0), v2", 0x0625_7227),
    ]);
    check_on(rv32, true, &[("vluxei32.v v4, (a0), v2", 0x0625_6207)]);
    check(128, e32(M1), 2, true, &[
        ("vluxei64.v v4, (a0), v2", 0x0625_7207),
        ("vsuxei64.v v4, (a0), v2", 0x0625_7227),
    ]);
}

#[test]
fn vfwmaccbf16_vf_destination_emul_above_8_is_reserved() {
    check(128, vt(16, M8), 4, false, &[("vfwmaccbf16.vf v0, fa1, v8", 0xEE85_D057)]);
    check(128, vt(16, M4), 4, true, &[("vfwmaccbf16.vf v0, fa1, v8", 0xEE85_D057)]);
}

#[test]
fn widening_fp_multiply_add_vf_with_vs2_in_vd_is_reserved() {
    // vd v16-v23 is also a source with EEW 32; vs2 v20-v23 has EEW 16.
    check(128, vt(16, M4), 4, false, &[
        ("vfwmacc.vf v16, fa1, v20", 0xF345_D857),
        ("vfwnmsac.vf v16, fa1, v20", 0xFF45_D857),
    ]);
    check(128, vt(16, M4), 4, true, &[
        ("vfwmacc.vf v16, fa1, v8", 0xF285_D857),
        // Not a multiply-add: vd is no source, so vs2 may sit in its upper half.
        ("vfwadd.vf v16, v20, fa1", 0xC345_D857),
    ]);
}

#[test]
fn vsha2_register_group_must_hold_a_4_sew_element_group() {
    // VLEN = 128: e64, m1 holds 128 of the 256 bits; e32, mf2 holds 64 of 128.
    check(128, vt(64, M1), 0, false, &[("vsha2ms.vv v4, v8, v12", 0xB686_2277)]);
    check(128, vt(32, MF2), 0, false, &[("vsha2ch.vv v4, v8, v12", 0xBA86_2277)]);
    check(128, vt(64, M2), 0, true, &[("vsha2ms.vv v4, v8, v12", 0xB686_2277)]);
    check(128, vt(32, M1), 4, true, &[("vsha2ch.vv v4, v8, v12", 0xBA86_2277)]);
}

#[test]
fn vrgatherei16_index_emul_above_8_is_reserved() {
    // e8, m8: the EEW 16 indices in vs1 would need EMUL = 16. These register
    // choices pass the overlap and alignment checks.
    let cases = [
        ("vrgatherei16.vv v24, v16, v0", 0x3B00_0C57),
        ("vrgatherei16.vv v0, v8, v16", 0x3A88_0057),
    ];
    check(128, vt(8, M8), 8, false, &cases);
    check(256, vt(8, M8), 8, false, &cases);
    check(128, vt(8, M4), 8, true, &[("vrgatherei16.vv v24, v16, v0", 0x3B00_0C57)]);
}

#[test]
fn zvkb_is_in_the_isa_string() {
    let isa = Oracle::new().isa_string();
    assert!(isa.contains("_zvkb_"), "{isa}");
}
