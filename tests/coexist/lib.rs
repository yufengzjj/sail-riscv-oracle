#[cfg(test)]
mod tests {
    /// add x3, x1, x2
    const RV_ADD_X3_X1_X2: u32 = 0x0020_81B3;
    /// ADD X0, X1, X2
    const A64_ADD_X0_X1_X2: u32 = 0x8B02_0020;

    #[test]
    fn riscv_and_aarch64_in_one_binary() {
        let mut rv = sail_riscv_oracle::Oracle::new();
        rv.set_x(1, 5);
        rv.set_x(2, 7);
        let step = rv.step(RV_ADD_X3_X1_X2);
        assert!(step.retired);
        assert_eq!(rv.get_x(3), 12);

        let mut arm = sail_aarch64_oracle::Oracle::new();
        arm.set_x(1, 3);
        arm.set_x(2, 4);
        arm.set_pc(0x1000);
        arm.step(A64_ADD_X0_X1_X2);
        assert_eq!(arm.get_x(0), 7);
        assert_eq!(arm.get_pc(), 0x1004);

        // Interleave once more: each model must still see only its own runtime state.
        let step = rv.step(RV_ADD_X3_X1_X2);
        assert!(step.retired);
        assert_eq!(rv.get_x(3), 12);
        assert_eq!(rv.get_pc(), sail_riscv_oracle::DEFAULT_RESET_PC + 8);
    }
}
