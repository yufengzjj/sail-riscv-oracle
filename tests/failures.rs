//! Model failures (Sail assertions, pattern-match failures, missing
//! configuration items, uncaught Sail exceptions) are errors, not process
//! exits.

use std::panic::{catch_unwind, AssertUnwindSafe};

use sail_riscv_oracle::{csr, Change, Oracle, RV64_CONFIG};

/// add x3, x1, x2
const ADD_X3_X1_X2: u32 = 0x0020_81B3;
/// wfi
const WFI: u32 = 0x1050_0073;
/// fadd.s f3, f1, f2 (rm = dyn)
const FADD_S_F3_F1_F2: u32 = 0x0020_F1D3;

fn panic_message(r: std::thread::Result<impl Sized>) -> String {
    let payload = match r {
        Ok(_) => panic!("expected a panic"),
        Err(p) => p,
    };
    if let Some(s) = payload.downcast_ref::<String>() {
        s.clone()
    } else if let Some(s) = payload.downcast_ref::<&str>() {
        s.to_string()
    } else {
        String::new()
    }
}

fn fresh_oracle_works() {
    let mut cpu = Oracle::new();
    cpu.set_x(1, 5);
    cpu.set_x(2, 7);
    let step = cpu.step(ADD_X3_X1_X2);
    assert_eq!(step.changes, vec![Change::X { reg: 3, value: 12 }]);
}

/// Every later call on a poisoned instance panics, and dropping it is fine.
fn assert_poisoned(mut cpu: Oracle) {
    assert!(cpu.is_poisoned());
    let msg = panic_message(catch_unwind(AssertUnwindSafe(|| cpu.get_pc())));
    assert!(msg.contains("poisoned"), "{msg}");
    let msg = panic_message(catch_unwind(AssertUnwindSafe(|| cpu.set_x(1, 1))));
    assert!(msg.contains("poisoned"), "{msg}");
    let msg = panic_message(catch_unwind(AssertUnwindSafe(|| cpu.try_step(ADD_X3_X1_X2))));
    assert!(msg.contains("poisoned"), "{msg}");
    drop(cpu);
    fresh_oracle_works();
}

#[test]
fn missing_config_key_is_a_build_error() {
    let without_xlen = RV64_CONFIG.replacen("\"xlen\": 64,", "", 1);
    assert_ne!(without_xlen, RV64_CONFIG);
    for _ in 0..3 {
        let err = Oracle::builder().config_json(without_xlen.clone()).build().err().unwrap();
        assert!(err.contains("Pattern match failure"), "{err}");
    }
    fresh_oracle_works();
}

#[test]
fn config_item_failing_inside_model_init_is_a_build_error() {
    // A top-level `let` in the model reads this item, so model_init fails
    // halfway.
    for _ in 0..3 {
        let err = Oracle::builder()
            .set("base.privileged_isa_version", "null")
            .build()
            .err()
            .unwrap();
        assert!(err.contains("Pattern match failure in let"), "{err}");
    }
    fresh_oracle_works();
}

#[test]
fn non_object_config_path_is_a_build_error() {
    let err = Oracle::builder().set("memory", "1").build().err().unwrap();
    assert!(err.contains("Failed to access configuration item"), "{err}");
    fresh_oracle_works();
}

#[test]
fn bad_config_item_read_during_a_step_poisons_the_instance() {
    // Only WFI reads platform.wfi_is_nop, so the model accepts the
    // configuration and fails in its pattern match on the value.
    let mut cpu = Oracle::builder().set("platform.wfi_is_nop", "null").build().unwrap();
    cpu.set_x(1, 5);
    cpu.set_x(2, 7);
    assert!(cpu.try_step(ADD_X3_X1_X2).is_ok());
    let err = cpu.try_step(WFI).unwrap_err();
    assert!(err.message().contains("Pattern match failure in wait_is_nop"), "{err}");
    assert_poisoned(cpu);
}

#[test]
fn uncaught_sail_exception_poisons_the_instance() {
    let mut cpu = Oracle::builder()
        .set("base.reserved_behavior.fcsr_rm", "\"Fcsr_RM_Fatal\"")
        .build()
        .unwrap();
    cpu.set_fcsr(0b101 << 5); // frm = reserved
    let err = cpu.try_step(FADD_S_F3_F1_F2).unwrap_err();
    assert!(err.message().contains("reserved behavior"), "{err}");
    assert!(err.message().contains("fcsr.FRM"), "{err}");
    assert_poisoned(cpu);
}

#[test]
fn step_panics_with_the_message() {
    let mut cpu = Oracle::builder().set("platform.wfi_is_nop", "null").build().unwrap();
    let msg = panic_message(catch_unwind(AssertUnwindSafe(|| cpu.step(WFI))));
    assert!(msg.contains("wait_is_nop"), "{msg}");
    assert_poisoned(cpu);
}

#[test]
fn failure_outside_a_step_poisons_the_instance() {
    let mut cpu = Oracle::builder()
        .set("base.reserved_behavior.xtvec_mode", "\"Xtvec_Fatal\"")
        .build()
        .unwrap();
    let msg = panic_message(catch_unwind(AssertUnwindSafe(|| {
        cpu.write_csr(csr::MTVEC, 0x8000_0002) // mode 2 is reserved
    })));
    assert!(msg.contains("reserved behavior"), "{msg}");
    assert_poisoned(cpu);
}
