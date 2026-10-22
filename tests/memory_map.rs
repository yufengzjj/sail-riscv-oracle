//! Memory regions added with `Builder::add_ram` or changed through
//! `Builder::set` array paths (RV64 unless the test name says RV32).

use sail_riscv_oracle::{csr, Oracle};

const RAM: u64 = 0x8000_0000;
const HIGH: u64 = 0x1_0000_0000;

/// add x3, x1, x2
const ADD_X3_X1_X2: u32 = 0x0020_81B3;
/// ld a1, 0(a0)
const LD_A1_0_A0: u32 = 0x0005_3583;
/// sd a2, 0(a0)
const SD_A2_0_A0: u32 = 0x00C5_3023;
/// lw a1, 0(a0)
const LW_A1_0_A0: u32 = 0x0005_2583;
/// sw a2, 0(a0)
const SW_A2_0_A0: u32 = 0x00C5_2023;
/// vle32.v v8, (a0)
const VLE32_V8_A0: u32 = 0x0205_6407;

const A0: u32 = 10;
const A1: u32 = 11;
const A2: u32 = 12;

const CAUSE_LOAD_ACCESS_FAULT: u64 = 5;
const CAUSE_STORE_ACCESS_FAULT: u64 = 7;

fn ready(mut cpu: Oracle) -> Oracle {
    cpu.write_csr(csr::MTVEC, RAM + 0x100);
    cpu
}

fn load_trap(cpu: &mut Oracle, addr: u64) -> Option<u64> {
    cpu.set_x(A0, addr);
    cpu.step(LD_A1_0_A0).trap().map(|(_, cause)| cause)
}

fn ram_region_json(base: u64, size: u64) -> String {
    format!(
        r#"{{"base": {{"len": 64, "value": "{base:#x}"}}, "size": {{"len": 64, "value": "{size:#x}"}},
        "attributes": {{"mem_type": "MainMemory", "cacheable": true, "coherent": true, "executable": true,
        "readable": true, "writable": true, "read_idempotent": true, "write_idempotent": true,
        "misaligned_exceptions": {{"load_store": {{"None": null}}, "vector": {{"None": null}},
        "amo": "AccessFault", "lrsc": "AccessFault"}}, "atomic_support": "AMOCASQ",
        "misaligned_atomicity_granule_size_exp": 4, "vector_misaligned_atomicity_granule_size_exp": 4,
        "reservability": "RsrvEventual", "supports_cbo_zero": true, "supports_pte_read": true,
        "supports_pte_write": true}}, "include_in_device_tree": false}}"#
    )
}

#[test]
fn ram_above_4_gib_loads_stores_and_fetches() {
    let mut cpu = ready(Oracle::builder().add_ram(HIGH, 0x1000_0000).build().unwrap());
    cpu.set_x(A0, HIGH + 0x0FFF_FFF8);
    cpu.set_x(A2, 0x1122_3344_5566_7788);
    assert!(cpu.step(SD_A2_0_A0).retired);
    assert_eq!(cpu.read_mem_u64(HIGH + 0x0FFF_FFF8), 0x1122_3344_5566_7788);
    assert!(cpu.step(LD_A1_0_A0).retired);
    assert_eq!(cpu.get_x(A1), 0x1122_3344_5566_7788);

    cpu.write_mem_u32(HIGH, ADD_X3_X1_X2);
    cpu.set_pc(HIGH);
    cpu.set_x(1, 2);
    cpu.set_x(2, 3);
    let step = cpu.step_fetch();
    assert!(step.retired, "{step:?}");
    assert_eq!(cpu.get_x(3), 5);
    assert_eq!(cpu.get_pc(), HIGH + 4);

    assert_eq!(load_trap(&mut cpu, HIGH + 0x1000_0000), Some(CAUSE_LOAD_ACCESS_FAULT));
}

#[test]
fn access_must_lie_within_one_region() {
    let mut cpu = ready(Oracle::builder().add_ram(HIGH, 0x1000_0000).build().unwrap());
    assert_eq!(load_trap(&mut cpu, HIGH - 4), Some(CAUSE_LOAD_ACCESS_FAULT));
    assert_eq!(cpu.read_csr(csr::MTVAL), Some(HIGH - 4));
    cpu.set_x(A0, HIGH - 4);
    let step = cpu.step(SD_A2_0_A0);
    assert_eq!(step.trap(), Some((false, CAUSE_STORE_ACCESS_FAULT)));

    let mut cpu = ready(
        Oracle::builder().set("memory.regions.2.size.value", "\"0x9000_0000\"").build().unwrap(),
    );
    assert_eq!(load_trap(&mut cpu, HIGH - 4), None);
}

#[test]
fn ram_below_the_other_regions_is_inserted_in_order() {
    let mut cpu = ready(Oracle::builder().add_ram(0, 0x1000).build().unwrap());
    cpu.set_x(A0, 0x8);
    cpu.set_x(A2, 42);
    assert!(cpu.step(SD_A2_0_A0).retired);
    assert_eq!(cpu.read_mem_u64(0x8), 42);
}

#[test]
fn regions_end_within_physaddr_bits() {
    let top = 0xFFFF_FFFF_8000_0000;
    assert!(Oracle::builder().add_ram(top, 0x8000_0000).build().is_err());
    assert!(Oracle::builder().add_ram(0xFF_FFFF_8000_0000, 0x8000_0000).build().is_ok());
    assert!(Oracle::builder().add_ram(0xFF_FFFF_8000_0000, 0x8000_1000).build().is_err());

    let mut cpu = ready(Oracle::new());
    assert_eq!(load_trap(&mut cpu, 0xFF00_0000_8000_0000), Some(CAUSE_LOAD_ACCESS_FAULT));
}

#[test]
fn ram_at_the_top_of_the_address_space() {
    let top = 0xFFFF_FFFF_8000_0000;
    let mut cpu = ready(
        Oracle::builder()
            .set("memory.physaddr_bits", "64")
            .add_ram(0, 0x1000)
            .add_ram(top, 0x8000_0000)
            .build()
            .unwrap(),
    );
    cpu.write_mem_u64(0xFFFF_FFFF_FFFF_FFF8, 0x0102_0304_0506_0708);
    assert_eq!(load_trap(&mut cpu, 0xFFFF_FFFF_FFFF_FFF8), None);
    assert_eq!(cpu.get_x(A1), 0x0102_0304_0506_0708);

    cpu.write_mem_u32(0, 0x0A0B_0C0D);
    assert_eq!(load_trap(&mut cpu, 0xFFFF_FFFF_FFFF_FFFC), None);
    assert_eq!(cpu.get_x(A1), 0x0A0B_0C0D_0102_0304);
}

#[test]
fn rv32_access_wraps_past_2_32() {
    let rv32 = || ready(Oracle::builder().rv32().vlen(128).add_ram(0, 0x1000).build().unwrap());
    let mut cpu = rv32();
    cpu.write_mem_u32(0xFFFF_FFFC, 0x4433_2211);
    cpu.write_mem_u32(0, 0x8877_6655);
    cpu.set_x(A0, 0xFFFF_FFFE);
    assert!(cpu.step(LW_A1_0_A0).retired);
    assert_eq!(cpu.get_x(A1), 0x6655_4433);
    cpu.set_x(A2, 0xDDCC_BBAA);
    assert!(cpu.step(SW_A2_0_A0).retired);
    assert_eq!(cpu.read_mem_u32(0xFFFF_FFFC), 0xBBAA_2211);
    assert_eq!(cpu.read_mem_u32(0), 0x8877_DDCC);

    let mut cpu = rv32();
    cpu.write_mem_u32(0xFFFF_FFFC, 0x4433_2211);
    cpu.write_mem_u32(0, 0x8877_6655);
    cpu.set_x(A0, 0xFFFF_FFFE);
    cpu.set_vtype(0x10); // e32, m1
    cpu.set_vl(1);
    assert!(cpu.step(VLE32_V8_A0).retired);
    assert_eq!(cpu.get_v(8)[0] & 0xFFFF_FFFF, 0x6655_4433);

    // Without memory at address 0 the part from there faults.
    let mut cpu = ready(Oracle::rv32());
    cpu.set_x(A0, 0xFFFF_FFFE);
    assert_eq!(cpu.step(LW_A1_0_A0).trap(), Some((false, CAUSE_LOAD_ACCESS_FAULT)));
    assert_eq!(cpu.read_csr(csr::MTVAL), Some(0));
}

#[test]
fn bad_regions_are_build_errors() {
    assert!(Oracle::builder().add_ram(HIGH + 0x800, 0x1000).build().is_err());
    assert!(Oracle::builder().add_ram(0x7000_0000, 0x2000_0000).build().is_err());
    let err = Oracle::builder()
        .set("memory.regions.2.attributes.mem_type", "\"IOMemory\"")
        .add_ram(HIGH, 0x1000)
        .build()
        .err()
        .unwrap();
    assert!(err.contains("no MainMemory region"), "{err}");
}

#[test]
fn set_with_an_array_index() {
    let rom = 0x1000;
    assert_eq!(load_trap(&mut ready(Oracle::new()), rom), None);
    let mut cpu = ready(
        Oracle::builder().set("memory.regions.0.attributes.readable", "false").build().unwrap(),
    );
    assert_eq!(load_trap(&mut cpu, rom), Some(CAUSE_LOAD_ACCESS_FAULT));

    let err = Oracle::builder()
        .set("memory.regions.3.attributes.executable", "false")
        .build()
        .err()
        .unwrap();
    assert!(err.contains("index 3 is out of range"), "{err}");
    let err = Oracle::builder().set("memory.regions.x", "1").build().err().unwrap();
    assert!(err.contains("does not name an object member or array element"), "{err}");
}

#[test]
fn set_appends_with_dash_and_keeps_every_append() {
    let mut cpu = ready(
        Oracle::builder()
            .set("memory.regions.-", ram_region_json(HIGH, 0x1000))
            .set("memory.regions.-", ram_region_json(HIGH + 0x2000, 0x1000))
            .build()
            .unwrap(),
    );
    assert_eq!(load_trap(&mut cpu, HIGH), None);
    assert_eq!(load_trap(&mut cpu, HIGH + 0x2000), None);
    assert_eq!(load_trap(&mut cpu, HIGH + 0x1000), Some(CAUSE_LOAD_ACCESS_FAULT));
}
