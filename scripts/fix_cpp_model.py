#!/usr/bin/env python3
"""Make the Sail --cpp output safe for several model instances per process.

Usage: fix_cpp_model.py path/to/model.cpp

The GMP scratch temporaries (zghz3*) are file-scope globals, but every
instance's model_init/model_fini runs the startup_z*/finish_z* calls that
create/kill them, so destroying one instance frees the scratch the others are
still using. -> guard the startup runs to the first live instance and the
finish runs to the last (refcounted); the per-instance parts stay untouched.
Idempotent.
"""
import os
import re
import sys

STARTUP = re.compile(r"^\s+startup_z[A-Za-z_0-9]+\(\);\s*$")
FINISH = re.compile(r"^\s+finish_z[A-Za-z_0-9]+\(\);\s*$")
GUARD_DECL = "static int sail_scratch_refs = 0; /* fix_cpp_model.py */\n"


def refcount_scratch(cpp_path: str) -> None:
    tmp_path = cpp_path + ".tmp"
    in_fn = None  # None | "init" | "fini"
    runs_wrapped = 0
    already = False
    with open(cpp_path) as src, open(tmp_path, "w") as dst:
        pending = []

        def flush(cond: str) -> None:
            nonlocal runs_wrapped
            if pending:
                dst.write(f"  if ({cond}) {{ /* fix_cpp_model.py */\n")
                dst.writelines(pending)
                dst.write("  }\n")
                pending.clear()
                runs_wrapped += 1

        for line in src:
            if line == GUARD_DECL:
                already = True
            if in_fn is None:
                if line.startswith("void Model::model_init(void)"):
                    in_fn = "init"
                    dst.write(GUARD_DECL + line + "{\n")
                    dst.write("  const bool sail_first = (sail_scratch_refs++ == 0);\n")
                    continue
                if line.startswith("void Model::model_fini(void)"):
                    in_fn = "fini"
                    dst.write(line + "{\n")
                    dst.write("  const bool sail_last = (--sail_scratch_refs == 0);\n")
                    continue
                dst.write(line)
                continue
            if line.startswith("{"):
                continue  # opening brace already emitted
            pat = STARTUP if in_fn == "init" else FINISH
            cond = "sail_first" if in_fn == "init" else "sail_last"
            if pat.match(line):
                pending.append(line)
                continue
            flush(cond)
            dst.write(line)
            if line.startswith("}"):
                in_fn = None
    if already:
        os.remove(tmp_path)
        print(f"{cpp_path}: scratch refcount already applied, skipped")
        return
    if runs_wrapped == 0:
        os.remove(tmp_path)
        sys.exit(f"{cpp_path}: no startup_/finish_ runs found in model_init/model_fini")
    os.replace(tmp_path, cpp_path)
    print(f"{cpp_path}: wrapped {runs_wrapped} startup/finish run(s) in refcount guards")


if __name__ == "__main__":
    refcount_scratch(sys.argv[1])
