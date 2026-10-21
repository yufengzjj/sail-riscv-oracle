//! The default configuration must run every unprivileged extension: one
//! representative instruction per extension has to retire without a trap.
//! Encodings come from LLVM 20's llvm-mc (Zibi and Zvabd are enabled too, but
//! llvm-mc does not know them yet).

use sail_riscv_oracle::Oracle;

const RAM: u64 = 0x8000_0000;
const A0: u32 = 10;
const A1: u32 = 11;
const A2: u32 = 12;

const VSETVLI_E64: u32 = 0x0D80_72D7; // vsetvli t0, zero, e64, m1, ta, ma
const VSETVLI_E32: u32 = 0x0D00_72D7; // vsetvli t0, zero, e32, m1, ta, ma
const VSETVLI_E16: u32 = 0x0C80_72D7; // vsetvli t0, zero, e16, m1, ta, ma

/// (extension, mnemonic, vsetvli to run first or 0, encoding)
const RV64_CASES: &[(&str, &str, u32, u32)] = &[
    ("I", "add a0, a1, a2", 0, 0x00C5_8533),
    ("M", "mul a0, a1, a2", 0, 0x02C5_8533),
    ("M", "divu a0, a1, a2", 0, 0x02C5_D533),
    ("Zalrsc", "lr.d a1, (a0)", 0, 0x1005_35AF),
    ("Zaamo", "amoadd.d a1, a2, (a0)", 0, 0x00C5_35AF),
    ("Zabha", "amoadd.b a1, a2, (a0)", 0, 0x00C5_05AF),
    ("Zacas", "amocas.d a1, a2, (a0)", 0, 0x28C5_35AF),
    ("Zacas", "amocas.q a2, a4, (a0)", 0, 0x28E5_462F),
    ("F", "fmadd.s fa0, fa1, fa2, fa3", 0, 0x68C5_F543),
    ("D", "fsqrt.d fa0, fa1", 0, 0x5A05_F553),
    ("Zfh", "fadd.h fa0, fa1, fa2", 0, 0x04C5_F553),
    ("Zfa", "fli.d fa0, 0.5", 0, 0xF216_0553),
    ("Zfa", "fminm.d fa0, fa1, fa2", 0, 0x2AC5_A553),
    ("Zfa", "fround.d fa0, fa1", 0, 0x4245_F553),
    ("Zfbfmin", "fcvt.bf16.s fa0, fa1", 0, 0x4485_F553),
    ("Zca", "c.add a1, a2", 0, 0x95B2),
    ("Zcd", "c.fld fa1, 0(a0)", 0, 0x210C),
    ("Zcb", "c.lbu a1, 0(a0)", 0, 0x810C),
    ("Zcmop", "c.mop.1", 0, 0x6081),
    ("Zba", "sh1add a0, a1, a2", 0, 0x20C5_A533),
    ("Zbb", "clz a0, a1", 0, 0x6005_9513),
    ("Zbs", "bset a0, a1, a2", 0, 0x28C5_9533),
    ("Zbc", "clmul a0, a1, a2", 0, 0x0AC5_9533),
    ("Zbkb", "pack a0, a1, a2", 0, 0x08C5_C533),
    ("Zbkx", "xperm8 a0, a1, a2", 0, 0x28C5_C533),
    ("Zknd", "aes64ds a0, a1, a2", 0, 0x3AC5_8533),
    ("Zkne", "aes64es a0, a1, a2", 0, 0x32C5_8533),
    ("Zknh", "sha256sig0 a0, a1", 0, 0x1025_9513),
    ("Zknh", "sha512sum0 a0, a1", 0, 0x1045_9513),
    ("Zksed", "sm4ed a0, a1, a2, 1", 0, 0x70C5_8533),
    ("Zksh", "sm3p0 a0, a1", 0, 0x1085_9513),
    ("Zicond", "czero.eqz a0, a1, a2", 0, 0x0EC5_D533),
    ("Zicbom", "cbo.clean (a0)", 0, 0x0015_200F),
    ("Zicboz", "cbo.zero (a0)", 0, 0x0045_200F),
    ("Zicbop", "prefetch.r 0(a0)", 0, 0x0015_6013),
    ("Zihintntl", "ntl.p1", 0, 0x0020_0033),
    ("Zihintpause", "pause", 0, 0x0100_000F),
    ("Zimop", "mop.r.0 a0, a1", 0, 0x81C5_C573),
    ("Zawrs", "wrs.nto", 0, 0x00D0_0073),
    ("Zicfilp", "lpad 0", 0, 0x0000_0017),
    ("Zicfiss", "sspopchk ra", 0, 0xCDC0_C073),
    ("Zicfiss", "ssrdp a0", 0, 0xCDC0_4573),
    ("Zicsr", "csrr a0, mscratch", 0, 0x3400_2573),
    ("Zifencei", "fence.i", 0, 0x0000_100F),
    ("Zicntr", "rdcycle a0", 0, 0xC000_2573),
    ("Zicntr", "rdtime a0", 0, 0xC010_2573),
    ("Zihpm", "csrr a0, hpmcounter3", 0, 0xC030_2573),
    ("V", "vadd.vv v3, v1, v2", VSETVLI_E64, 0x0211_01D7),
    ("V", "vfadd.vv v3, v1, v2", VSETVLI_E64, 0x0211_11D7),
    ("V", "vle64.v v3, (a0)", VSETVLI_E64, 0x0205_7187),
    ("V", "vredsum.vs v3, v1, v2", VSETVLI_E64, 0x0211_21D7),
    ("Zvfh", "vfadd.vv v3, v1, v2 (e16)", VSETVLI_E16, 0x0211_11D7),
    ("Zvbb", "vandn.vv v3, v2, v1", VSETVLI_E64, 0x0620_81D7),
    ("Zvbb", "vbrev.v v3, v2", VSETVLI_E64, 0x4A25_21D7),
    ("Zvbc", "vclmul.vv v3, v2, v1", VSETVLI_E64, 0x3220_A1D7),
    ("Zvkg", "vghsh.vv v3, v2, v1", VSETVLI_E32, 0xB220_A1F7),
    ("Zvkned", "vaesef.vv v3, v2", VSETVLI_E32, 0xA221_A1F7),
    ("Zvknhb", "vsha2ms.vv v3, v2, v1 (e64)", VSETVLI_E64, 0xB620_A1F7),
    ("Zvksed", "vsm4k.vi v3, v2, 1", VSETVLI_E32, 0x8620_A1F7),
    ("Zvksh", "vsm3me.vv v3, v2, v1", VSETVLI_E32, 0x8220_A1F7),
    ("Zvfbfmin", "vfncvtbf16.f.f.w v1, v4", VSETVLI_E16, 0x4A4E_90D7),
    ("Zvfbfwma", "vfwmaccbf16.vv v4, v1, v2", VSETVLI_E16, 0xEE20_9257),
];

const RV32_CASES: &[(&str, &str, u32, u32)] = &[
    ("Zcf", "c.flw fa1, 0(a0)", 0, 0x610C),
    ("Zkne", "aes32esi a0, a1, a2, 1", 0, 0x62C5_8533),
    ("Zknh", "sha512sum0r a0, a1, a2", 0, 0x50C5_8533),
    ("Zbkb", "zip a0, a1", 0, 0x08F5_9513),
    ("Zicfiss", "sspush ra", 0, 0xCE10_4073),
];

fn run(mut cpu: Oracle, cases: &[(&str, &str, u32, u32)]) {
    let mut failures = Vec::new();
    for &(ext, asm, vset, opcode) in cases {
        cpu.set_x(A0, RAM + 0x1000);
        cpu.set_x(A1, 3);
        cpu.set_x(A2, 7);
        if vset != 0 {
            cpu.step(vset);
        }
        let step = cpu.step(opcode);
        if !step.retired || step.trap().is_some() {
            failures.push(format!("{ext}: {asm} ({opcode:#010x}) -> trap {:?}", step.trap()));
        }
    }
    assert!(failures.is_empty(), "not executed:\n{}", failures.join("\n"));
}

#[test]
fn rv64_runs_every_unprivileged_extension() {
    run(Oracle::new(), RV64_CASES);
}

#[test]
fn rv32_specific_encodings() {
    run(Oracle::rv32(), RV32_CASES);
}
