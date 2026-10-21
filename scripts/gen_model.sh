#!/bin/sh
# Regenerate the C++ model (sail-riscv + sail/patches + sail/harness.sail) and
# refresh vendor/.
#
# Usage: scripts/gen_model.sh [path/to/sail-riscv] [out-dir]
#   sail-riscv defaults to ~/sail-riscv, out-dir to <sail-riscv>/build/oracle.
# The model is built from a clean worktree of the sail-riscv checkout's HEAD
# (<out-dir>/src) with sail/patches/*.patch applied; uncommitted changes in
# the checkout are not used.
# Needs `sail` (>= the version in sail-riscv's cmake/sail_required_version.txt)
# and z3 on PATH (`source env.sh`). Set NO_VENDOR=1 to leave vendor/ alone.
set -eu

here=$(cd "$(dirname "$0")/.." && pwd)
riscv=$(cd "${1:-$HOME/sail-riscv}" && pwd)
out=${2:-$riscv/build/oracle}
mkdir -p "$out"
out=$(cd "$out" && pwd)
base=$(git -C "$riscv" rev-parse HEAD)

src=$out/src
if [ -e "$src" ]; then
    git -C "$riscv" worktree remove --force "$src" 2>/dev/null || rm -rf "$src"
fi
git -C "$riscv" worktree prune
git -C "$riscv" worktree add --quiet --detach "$src" "$base"
for p in "$here"/sail/patches/*.patch; do
    [ -e "$p" ] || continue
    git -C "$src" apply "$p"
    echo "applied $(basename "$p")"
done
sail_ver=$(tr -d '[:space:]' < "$src/cmake/sail_required_version.txt")

harness_fns="
oracle_init oracle_xlen oracle_flen oracle_vlen oracle_elen
oracle_has_fregs oracle_has_vregs
oracle_get_x oracle_set_x oracle_get_pc oracle_set_pc
oracle_get_f oracle_set_f oracle_get_fcsr oracle_set_fcsr
oracle_get_v_chunk oracle_set_v_chunk
oracle_get_vl oracle_set_vl oracle_get_vtype oracle_set_vtype
oracle_get_vstart oracle_set_vstart oracle_get_vcsr oracle_set_vcsr
oracle_get_priv oracle_set_priv
oracle_csr_readable oracle_read_csr oracle_write_csr
"
# Model entry points the shim calls directly.
model_fns="
init_model try_step set_pc_reset_address config_is_valid
dispatchEventCounter event_selector_width rvfi_set_instr_packet
generate_canonical_isa_string
"
preserve=""
for f in $harness_fns $model_fns; do
    preserve="$preserve --c-preserve $f"
done

cd "$src/model"
# Same flags as the C++ target in sail-riscv's model/CMakeLists.txt.
# shellcheck disable=SC2086
sail \
    --strict-var --strict-bitvector --strict-exponentials \
    --require-version "$sail_ver" \
    --memo-z3 --memo-z3-path "$out/sail_smt_cache" \
    -o "$out/sail_riscv_model" \
    -O --Oconstant-fold \
    --cpp \
    --cpp-namespace hart \
    --cpp-derive-from "protected PlatformInterface" \
    --c-no-main \
    --c-header-include riscv_platform_if.h \
    --c-include riscv_softfloat.h \
    $preserve \
    --all-modules \
    riscv.sail_project "$here/sail/oracle.sail_project"

python3 "$here/scripts/fix_cpp_model.py" "$out/sail_riscv_model.cpp"

missing=0
for f in $harness_fns; do
    mangled=z$(printf '%s' "$f" | sed 's/z/zz/g')
    grep -q "Model::$mangled(" "$out/sail_riscv_model.cpp" || { echo "missing in output: $f" >&2; missing=1; }
done
[ "$missing" -eq 0 ] || exit 1

if [ "${NO_VENDOR:-0}" != 1 ]; then
    gzip -9 -c "$out/sail_riscv_model.cpp" > "$here/vendor/sail_riscv_model.cpp.gz"
    cp "$out/sail_riscv_model.h" "$here/vendor/sail_riscv_model.h"
    echo "$base" > "$here/vendor/SAIL_RISCV_COMMIT"
    echo "vendor/ refreshed from sail-riscv $(cat "$here/vendor/SAIL_RISCV_COMMIT")"
fi
