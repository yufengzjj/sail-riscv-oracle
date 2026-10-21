# Environment for regenerating the model in WSL2 (Alpine). Usage:  source env.sh
#
# The default `cargo build` is self-contained (vendored model + runtime) and
# needs NONE of this; it is only for scripts/gen_model.sh.

eval "$(opam env --switch=5.3.0)"                      # sail 0.20.3
export PATH="$HOME/.local/usr/bin:$HOME/.local/bin:$PATH"  # z3 (rootless), ninja
