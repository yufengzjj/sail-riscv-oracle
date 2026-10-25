//! Build script: compile the Sail C++ model class + sail-riscv's platform and
//! SoftFloat glue + the C Sail runtime + SoftFloat + shim.
//!
//! Every C/C++ file force-includes csrc/sailrv_prefix.h, which renames the
//! global names of the runtime, SoftFloat, mini-gmp and model to `sailrv_*`,
//! so other Sail-based crates (with their own copies) can link into the same
//! binary. Regenerate it with scripts/gen_prefix_header.sh.
//!
//! On Windows MSVC the static libraries are linked into `$OUT_DIR/sailrv.dll` (see
//! `link_dll`) instead of into each program; src/native.rs loads it.
//!
//! Default is fully self-contained — vendored pre-generated model + patched
//! runtime with bundled mini-gmp, no Sail/GMP/zlib. Env overrides for building
//! against a freshly generated model (see README "Regenerating the model"):
//!   RISCV_ORACLE_SAIL_MODEL_C    path to the generated sail_riscv_model.cpp
//!   RISCV_ORACLE_SAIL_MODEL_INC  extra include dir (default: dir of the .cpp)
//!                  Prefixed so another Sail-based crate's model override can't
//!                  leak into this one.
//!   SAIL_LIB_DIR   external (opam) Sail runtime dir; implies system GMP + zlib
//!   SAIL_SYSTEM_GMP=1  link real libgmp instead of bundled mini-gmp (also OK on
//!                  Windows: sail.h's LLP64 patch keeps 64-bit values intact).
//!                  Consumer-facing equivalent: the `system-gmp` cargo feature
//!                  (`system-gmp-static` for static linking). Auto-discovery
//!                  order: GMP_DIR, INCLUDE/LIB, structured PATH scan (bin/prefix
//!                  -> include|lib), gmp files directly on PATH, toolchain default.
//!   GMP_DIR        prefix of a custom libgmp; uses $GMP_DIR/{include,lib}
//!   GMP_INCLUDE_DIR / GMP_LIB_DIR  override either half of GMP_DIR
//!   GMP_LIB_NAME (default "gmp") / GMP_STATIC=1  link name / link statically
//!   ZLIB_LIB_DIR / ZLIB_LIB_NAME  zlib link tweaks (external runtime only)
//! The native model/runtime is force-built at >= -O2 (the exact-rational FP
//! paths are unusably slow at -O0); SAIL_MODEL_DEBUG=1 inherits the cargo
//! profile's own opt-level instead, for a fast unoptimized compile.

use std::env;
use std::path::{Path, PathBuf};

fn unpack_vendored_model(vendor: &Path) -> PathBuf {
    let gz = vendor.join("sail_riscv_model.cpp.gz");
    assert!(
        gz.is_file(),
        "vendor/sail_riscv_model.cpp.gz is missing and RISCV_ORACLE_SAIL_MODEL_C is not set. \
         Either restore the vendored model or generate one (scripts/gen_model.sh)."
    );
    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    let out = out_dir.join("sail_riscv_model.cpp");
    let stamp = out_dir.join("sail_riscv_model.cpp.gz.trailer");

    // OUT_DIR can be shared by different versions of this crate (e.g. after
    // rolling Cargo.lock back), so mtimes can't tell which model is unpacked.
    // The gzip trailer (CRC32 + size of the unpacked data) identifies it.
    let data = std::fs::read(&gz).expect("read model.cpp.gz");
    let trailer = &data[data.len().saturating_sub(8)..];
    let fresh = out.is_file() && std::fs::read(&stamp).is_ok_and(|s| s == trailer);
    if !fresh {
        let _ = std::fs::remove_file(&stamp);
        let mut reader = flate2::read::GzDecoder::new(&data[..]);
        let mut writer = std::io::BufWriter::new(
            std::fs::File::create(&out).expect("create OUT_DIR/sail_riscv_model.cpp"),
        );
        std::io::copy(&mut reader, &mut writer).expect("decompress sail_riscv_model.cpp.gz");
        std::io::Write::flush(&mut writer).expect("write OUT_DIR/sail_riscv_model.cpp");
        std::fs::write(&stamp, trailer).expect("write OUT_DIR/sail_riscv_model.cpp.gz.trailer");
    }
    out
}

/// Copy the SoftFloat sources with every `softfloat_*` identifier renamed to
/// `sailrv_softfloat_*`. A rename macro cannot do this: SoftFloat tests its
/// own names with `#ifndef softfloat_*` and would then skip their code.
fn copy_prefixed_softfloat(src: &Path, dst: &Path) {
    std::fs::create_dir_all(dst).expect("create OUT_DIR/softfloat");
    for entry in std::fs::read_dir(src).expect("read vendor/softfloat") {
        let path = entry.expect("read vendor/softfloat").path();
        let out = dst.join(path.file_name().unwrap());
        if path.is_dir() {
            copy_prefixed_softfloat(&path, &out);
            continue;
        }
        if !path.extension().is_some_and(|x| x == "c" || x == "h") {
            continue;
        }
        let text = std::fs::read_to_string(&path).expect("read SoftFloat source");
        let mut new = String::with_capacity(text.len() + text.len() / 8);
        for line in text.split_inclusive('\n') {
            if line.trim_start().starts_with("#include") {
                new.push_str(line);
                continue;
            }
            let bytes = line.as_bytes();
            let mut start = 0;
            for (i, _) in line.match_indices("softfloat_") {
                if i == 0 || !(bytes[i - 1].is_ascii_alphanumeric() || bytes[i - 1] == b'_') {
                    new.push_str(&line[start..i]);
                    new.push_str("sailrv_");
                    start = i;
                }
            }
            new.push_str(&line[start..]);
        }
        if std::fs::read_to_string(&out).ok().as_deref() != Some(new.as_str()) {
            std::fs::write(&out, new).expect("write OUT_DIR/softfloat");
        }
    }
}

/// Inspect a `!<arch>` archive (`*.lib`/`*.a`) and report whether it is a real
/// static library rather than a DLL import library. MSVC names both `*.lib`, so
/// the filename can't tell them apart — only the content can. Two import-lib
/// signatures are checked, covering both formats Windows uses:
///   * *short* import (classic MSVC `lib`): members begin with the IMPORT_OBJECT
///     magic `00 00 FF FF` (Machine = UNKNOWN, Sig2 = 0xFFFF);
///   * *long* import (dlltool/lld style, e.g. vcpkg's gmp): members are ordinary
///     COFF objects but every member is *named after the DLL* (`*.dll`), which is
///     also recorded in the `//` long-names table.
/// A static archive's members are `*.o`/`*.obj` and reference no DLL. Returns
/// Some(true)=static, Some(false)=import lib, or None if the file isn't a
/// parseable archive (the caller then trusts it rather than false-rejecting).
fn archive_is_static(lib: &Path) -> Option<bool> {
    const MAGIC: &[u8] = b"!<arch>\n";
    let data = std::fs::read(lib).ok()?;
    if !data.starts_with(MAGIC) {
        return None; // not an ar archive (e.g. a bare .so handed to us)
    }
    let dll_named = |s: &str| s.trim_end_matches('/').to_ascii_lowercase().ends_with(".dll");
    let mut pos = MAGIC.len();
    let mut saw_real_member = false;
    while pos + 60 <= data.len() {
        let header = &data[pos..pos + 60];
        let name = std::str::from_utf8(&header[0..16]).ok()?.trim_end();
        let size: usize = std::str::from_utf8(&header[48..58]).ok()?.trim().parse().ok()?;
        let body = pos + 60;
        let end = body.checked_add(size)?;
        if end > data.len() {
            return None;
        }
        let bytes = &data[body..end];
        if name == "//" {
            // Long-names table: a DLL name parked here means a (long) import lib.
            if bytes.windows(4).any(|w| w.eq_ignore_ascii_case(b".dll")) {
                return Some(false);
            }
        } else if !(name.is_empty() || name == "/") {
            saw_real_member = true;
            if bytes.starts_with(&[0x00, 0x00, 0xFF, 0xFF]) || dll_named(name) {
                return Some(false);
            }
        }
        pos = end + (size & 1); // members are 2-byte aligned
    }
    if saw_real_member {
        Some(true)
    } else {
        None
    }
}

/// True if `dir` holds a linkable gmp (any platform's naming). When `static_only`
/// (the `system-gmp-static` path), require a static archive — a `.so`/`.dylib`-only
/// prefix won't satisfy a `static=gmp` link, and a `*.lib` that's actually a DLL
/// import library is rejected via `archive_is_static` (an unparseable archive is
/// trusted rather than false-rejected) so discovery keeps scanning for a real one.
fn gmp_lib_present(dir: &Path, static_only: bool) -> bool {
    for name in ["gmp.lib", "libgmp.a"] {
        let p = dir.join(name);
        if p.is_file() {
            if static_only && archive_is_static(&p) == Some(false) {
                continue;
            }
            return true;
        }
    }
    if static_only {
        return false;
    }
    for name in ["libgmp.so", "libgmp.dylib"] {
        if dir.join(name).is_file() {
            return true;
        }
    }
    // Versioned shared objects (libgmp.so.10, ...).
    std::fs::read_dir(dir)
        .map(|rd| {
            rd.filter_map(Result::ok)
                .any(|e| e.file_name().to_string_lossy().starts_with("libgmp.so"))
        })
        .unwrap_or(false)
}

/// First dir in a `;`/`:`-separated env path-list (e.g. MSVC's INCLUDE / LIB)
/// that satisfies `pred`.
fn find_dir_in_env(var: &str, pred: impl Fn(&Path) -> bool) -> Option<PathBuf> {
    env::var_os(var).and_then(|v| env::split_paths(&v).find(|d| pred(d)))
}

/// Scan PATH for a system GMP and return (include_dir, lib_dir); either may be
/// None, in which case the toolchain's default search path is relied on for
/// that half. For each PATH entry it probes the dir itself, `<dir>/include`
/// (`/lib`), and the sibling `<dir>/../include` (`/../lib`) — so it works
/// whether a bin/ or the prefix is on PATH, or (common on Windows) the include/
/// and lib/ dirs themselves are, even as separate PATH entries.
fn scan_path_for_gmp(static_only: bool) -> (Option<PathBuf>, Option<PathBuf>) {
    let path = match env::var_os("PATH") {
        Some(p) => p,
        None => return (None, None),
    };
    let mut inc = None;
    let mut lib = None;
    for dir in env::split_paths(&path) {
        let sibling = dir.parent().map(Path::to_path_buf);
        if inc.is_none() {
            let mut cands = vec![dir.join("include")];
            cands.extend(sibling.as_ref().map(|p| p.join("include")));
            inc = cands.into_iter().find(|c| c.join("gmp.h").is_file());
        }
        if lib.is_none() {
            let mut cands = vec![dir.join("lib")];
            cands.extend(sibling.as_ref().map(|p| p.join("lib")));
            lib = cands.into_iter().find(|c| gmp_lib_present(c, static_only));
        }
        if inc.is_some() && lib.is_some() {
            break;
        }
    }
    (inc, lib)
}

/// Last-resort PATH rule: gmp.h and a gmp lib sitting DIRECTLY in PATH dirs (the
/// two may be different entries). Catches installs that don't follow the
/// bin/include/lib prefix convention — anything that just dumped the files into
/// a dir that happens to be on PATH.
fn scan_path_flat(static_only: bool) -> (Option<PathBuf>, Option<PathBuf>) {
    let path = match env::var_os("PATH") {
        Some(p) => p,
        None => return (None, None),
    };
    let mut inc = None;
    let mut lib = None;
    for dir in env::split_paths(&path) {
        if inc.is_none() && dir.join("gmp.h").is_file() {
            inc = Some(dir.clone());
        }
        if lib.is_none() && gmp_lib_present(&dir, static_only) {
            lib = Some(dir.clone());
        }
        if inc.is_some() && lib.is_some() {
            break;
        }
    }
    (inc, lib)
}

fn main() {
    for key in [
        "RISCV_ORACLE_SAIL_MODEL_C", "RISCV_ORACLE_SAIL_MODEL_INC",
        "SAIL_LIB_DIR", "SAIL_SYSTEM_GMP", "SAIL_MODEL_DEBUG",
        "GMP_DIR", "GMP_INCLUDE_DIR", "GMP_LIB_DIR", "GMP_LIB_NAME", "GMP_STATIC",
        "ZLIB_LIB_DIR", "ZLIB_LIB_NAME",
    ] {
        println!("cargo:rerun-if-env-changed={key}");
    }

    let vendor = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap()).join("vendor");

    let (model_src, model_inc) = match env::var("RISCV_ORACLE_SAIL_MODEL_C") {
        Ok(p) => {
            let src = PathBuf::from(p);
            assert!(src.is_file(), "RISCV_ORACLE_SAIL_MODEL_C does not exist: {src:?}");
            let inc = env::var("RISCV_ORACLE_SAIL_MODEL_INC")
                .map(PathBuf::from)
                .unwrap_or_else(|_| src.parent().unwrap().to_path_buf());
            (src, inc)
        }
        Err(_) => (unpack_vendored_model(&vendor), vendor.clone()),
    };

    // Runtime selection: default = vendored patched runtime (self-contained,
    // bundled mini-gmp, no elf.c/zlib); SAIL_LIB_DIR = external runtime (system
    // GMP + zlib); SAIL_SYSTEM_GMP or the `system-gmp` feature = vendored sources
    // but real libgmp (`system-gmp-static`/GMP_STATIC for static linking).
    let feature_system_gmp = env::var_os("CARGO_FEATURE_SYSTEM_GMP").is_some();
    let system_runtime = env::var_os("SAIL_LIB_DIR").is_some();
    let system_gmp =
        system_runtime || feature_system_gmp || env::var_os("SAIL_SYSTEM_GMP").is_some();
    let gmp_static = env::var_os("CARGO_FEATURE_SYSTEM_GMP_STATIC").is_some()
        || env::var_os("GMP_STATIC").is_some();
    let sail_lib = env::var("SAIL_LIB_DIR")
        .map(PathBuf::from)
        .unwrap_or_else(|_| vendor.join("sail-runtime"));
    assert!(sail_lib.is_dir(), "Sail runtime dir does not exist: {sail_lib:?}");

    // Resolve the system GMP's include/lib dirs (explicit env wins, else discover
    // per the module-doc order). Feeding the header path through cc's .include()
    // is portable across MSVC and gcc, so consumers don't hand-set CPATH/CFLAGS.
    let gmp_dir = env::var_os("GMP_DIR").map(PathBuf::from);
    let explicit_include = env::var_os("GMP_INCLUDE_DIR")
        .map(PathBuf::from)
        .or_else(|| gmp_dir.as_ref().map(|p| p.join("include")));
    let explicit_lib = env::var_os("GMP_LIB_DIR")
        .map(PathBuf::from)
        .or_else(|| gmp_dir.as_ref().map(|p| p.join("lib")));
    let (gmp_include, gmp_lib_dir) = if explicit_include.is_some() || explicit_lib.is_some() {
        (explicit_include, explicit_lib)
    } else if system_gmp {
        let (s_inc, s_lib) = scan_path_for_gmp(gmp_static);
        let (f_inc, f_lib) = scan_path_flat(gmp_static);
        let inc = find_dir_in_env("INCLUDE", |d| d.join("gmp.h").is_file())
            .or(s_inc)
            .or(f_inc);
        let lib = find_dir_in_env("LIB", |d| gmp_lib_present(d, gmp_static))
            .or(s_lib)
            .or(f_lib);
        (inc, lib)
    } else {
        (None, None)
    };

    // Hard guarantee: an explicit system-gmp request never silently falls back to
    // the bundled mini-gmp. Probe that <gmp.h> compiles and fail loudly now,
    // rather than grinding through the whole model build into a cryptic error.
    if system_gmp {
        let out = PathBuf::from(env::var("OUT_DIR").unwrap());
        let probe_src = out.join("gmp_probe.c");
        std::fs::write(
            &probe_src,
            "#include <gmp.h>\nint sail_gmp_probe(void){mpz_t z;mpz_init(z);mpz_clear(z);return 0;}\n",
        )
        .expect("write gmp probe source");
        let mut probe = cc::Build::new();
        probe.file(&probe_src).cargo_metadata(false).warnings(false);
        if let Some(inc) = &gmp_include {
            probe.include(inc);
        }
        if probe.try_compile("sail_gmp_probe").is_err() {
            panic!(
                "system-gmp is requested (cargo feature `system-gmp`/`system-gmp-static` or \
                 SAIL_SYSTEM_GMP) but <gmp.h> could not be compiled. Point the build at a libgmp \
                 via GMP_DIR=<prefix> (with include/ and lib/), GMP_INCLUDE_DIR/GMP_LIB_DIR, \
                 INCLUDE/LIB, PATH, or a system-wide install. This build does NOT fall back to \
                 the bundled mini-gmp."
            );
        }
    }

    // Floor the native model/runtime at -O2 even in dev builds: at the cargo
    // dev profile's -O0 the exact-rational FP paths (hundreds of mpq ops per
    // instruction) run ~20-50x slower, and this generated code is never
    // single-stepped, so there is no reason to leave it unoptimized.
    // SAIL_MODEL_DEBUG=1 opts out (inherit the profile's level verbatim) for a
    // fast unoptimized compile when runtime speed doesn't matter.
    let model_opt = if env::var_os("SAIL_MODEL_DEBUG").is_some() {
        env::var("OPT_LEVEL").unwrap_or_else(|_| "0".to_string())
    } else {
        match env::var("OPT_LEVEL").as_deref() {
            Ok("2") | Ok("3") | Ok("s") | Ok("z") => env::var("OPT_LEVEL").unwrap(),
            _ => "2".to_string(),
        }
    };

    let prefix_header = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap())
        .join("csrc")
        .join("sailrv_prefix.h");
    let common_flags = |b: &mut cc::Build| {
        b.opt_level_str(&model_opt);
        if b.get_compiler().is_like_msvc() {
            b.flag(format!("/FI{}", prefix_header.display()));
        } else {
            b.flag("-include").flag(&prefix_header);
        }
        // Sail-generated code is not warning-clean; keep logs readable.
        b.flag_if_supported("-Wno-unused")
            .flag_if_supported("-Wno-unused-parameter")
            .flag_if_supported("-Wno-unused-but-set-variable")
            .flag_if_supported("-Wno-sign-compare")
            .flag_if_supported("-Wno-extra");
    };

    let riscv = vendor.join("riscv");
    let softfloat = PathBuf::from(env::var("OUT_DIR").unwrap()).join("softfloat");
    copy_prefixed_softfloat(&vendor.join("softfloat"), &softfloat);

    // ---- 1) C++: generated model class + platform/SoftFloat glue + shim ----
    // Must be compiled FIRST: the model archive references runtime symbols, so
    // it must precede libsailriscv_runtime on traditional linkers.
    // C++20 required: generated code uses designated initializers + the `not`
    // token; MSVC needs /std:c++20 (implies /permissive-) for those.
    let mut cxx = cc::Build::new();
    cxx.cpp(true)
        .std("c++20")
        .include(&sail_lib)
        .include(&model_inc)
        .include(&riscv)
        .include(softfloat.join("source/include"))
        .include("csrc")
        // MSVC: model object exceeds the default COFF section limit.
        .flag_if_supported("/bigobj")
        .file(&model_src)
        .file(riscv.join("riscv_platform_if.cpp"))
        .file(riscv.join("riscv_softfloat.cpp"))
        .file("csrc/shim.cpp");
    common_flags(&mut cxx);
    // The shim's sail_fatal throws through the extern "C" runtime functions
    // the model calls; /EHsc would let MSVC assume those never throw.
    if cxx.get_compiler().is_like_msvc() {
        cxx.flag("/EHs");
    }
    if system_gmp {
        cxx.define("SAIL_SYSTEM_GMP", None); // sail.h: include <gmp.h>
        if let Some(inc) = &gmp_include {
            cxx.include(inc);
        }
    }
    let target_env = env::var("CARGO_CFG_TARGET_ENV").unwrap_or_default();
    let dll = env::var("CARGO_CFG_TARGET_OS").as_deref() == Ok("windows") && target_env == "msvc";
    let mut libs = Vec::new();
    compile(&mut cxx, "sailriscv_model", dll, &mut libs);

    // ---- 2) C: Sail runtime -------------------------------------------------
    let mut crt = cc::Build::new();
    crt.include(&sail_lib)
        .flag_if_supported("/std:c11") // timespec_get etc. under MSVC
        .file(sail_lib.join("sail.c"))
        .file(sail_lib.join("rts.c"));
    common_flags(&mut crt);
    // C++ exceptions from sail_fatal unwind through these C frames.
    if !crt.get_compiler().is_like_msvc() {
        crt.flag("-fexceptions");
    }
    // Sail >= 0.18 split the runtime: sail_assert (sail_failure.c) and
    // sail_config.c (needs cJSON.c) are referenced by the generated code.
    for extra in ["sail_failure.c", "sail_config.c", "cJSON.c"] {
        let p = sail_lib.join(extra);
        if p.is_file() {
            crt.file(p);
        }
    }
    if system_gmp {
        crt.define("SAIL_SYSTEM_GMP", None);
        if let Some(inc) = &gmp_include {
            crt.include(inc);
        }
    } else {
        crt.file(vendor.join("sail-runtime/mini-gmp.c"))
            .file(vendor.join("sail-runtime/mini-mpq.c"));
    }
    if system_runtime {
        // Only external runtimes compile elf.c; the model references nothing in it.
        crt.file(sail_lib.join("elf.c"));
    }
    compile(&mut crt, "sailriscv_runtime", dll, &mut libs);

    // ---- 3) C: Berkeley SoftFloat 3 (RISC-V specialization) -----------------
    // Same defines as sail-riscv's dependencies/softfloat/CMakeLists.txt; the
    // *M (multi-word) sources that conflict with SOFTFLOAT_FAST_INT64 are not
    // vendored. platform.h replaces the per-target build/ directory.
    let mut sf = cc::Build::new();
    sf.include(&softfloat)
        .include(softfloat.join("source/include"))
        .include(softfloat.join("source/RISCV"))
        .flag_if_supported("/std:c11")
        .define("SOFTFLOAT_ROUND_ODD", None)
        .define("INLINE_LEVEL", "5")
        .define("SOFTFLOAT_FAST_DIV32TO16", None)
        .define("SOFTFLOAT_FAST_DIV64TO32", None)
        .define("SOFTFLOAT_FAST_INT64", None);
    for dir in ["source", "source/RISCV"] {
        let mut srcs: Vec<PathBuf> = std::fs::read_dir(vendor.join("softfloat").join(dir))
            .expect("read vendor/softfloat")
            .filter_map(Result::ok)
            .map(|e| e.path())
            .filter(|p| p.extension().is_some_and(|x| x == "c"))
            .map(|p| softfloat.join(dir).join(p.file_name().unwrap()))
            .collect();
        srcs.sort();
        sf.files(srcs);
    }
    common_flags(&mut sf);
    sf.flag_if_supported("-Wno-implicit-fallthrough");
    compile(&mut sf, "sailriscv_softfloat", dll, &mut libs);

    if system_gmp && gmp_static {
        check_static_gmp(gmp_lib_dir.as_deref());
    }
    println!("cargo:rustc-check-cfg=cfg(sailrv_dll)");
    if dll {
        link_dll(&libs, gmp_lib_dir.as_deref(), system_gmp, gmp_static, system_runtime);
    } else {
        emit_link_deps(gmp_lib_dir.as_deref(), system_gmp, gmp_static, system_runtime, &target_env);
    }

    for p in [
        model_src.as_path(),
        Path::new("vendor/sail_riscv_model.cpp.gz"),
        Path::new("vendor/sail_riscv_model.h"),
        Path::new("vendor/sail-runtime"),
        Path::new("vendor/riscv"),
        Path::new("vendor/softfloat"),
        Path::new("csrc/shim.cpp"),
        Path::new("csrc/sailrv_prefix.h"),
        Path::new("src"),
        Path::new("build.rs"),
    ] {
        println!("cargo:rerun-if-changed={}", p.display());
    }
}

fn gmp_lib_name() -> String {
    env::var("GMP_LIB_NAME").unwrap_or_else(|_| "gmp".into())
}

fn zlib_lib_name(target_env: &str) -> String {
    env::var("ZLIB_LIB_NAME").unwrap_or_else(|_| if target_env == "msvc" { "zlib".into() } else { "z".into() })
}

/// For the DLL the static library is not announced to cargo but linked into the DLL, which
/// takes only the members it needs, as a static link does.
fn compile(b: &mut cc::Build, name: &str, dll: bool, libs: &mut Vec<PathBuf>) {
    if dll {
        b.cargo_metadata(false);
        libs.push(PathBuf::from(env::var("OUT_DIR").unwrap()).join(format!("{name}.lib")));
    }
    b.compile(name);
}

/// Links the static libraries into `$OUT_DIR/sailrv.dll`, exporting every `sailrv_*`
/// function the Rust sources call, and copies gmp's DLL beside it.
fn link_dll(libs: &[PathBuf], gmp_lib_dir: Option<&Path>, system_gmp: bool, gmp_static: bool, system_runtime: bool) {
    let out = PathBuf::from(env::var("OUT_DIR").unwrap());
    let mut exports: Vec<String> = Vec::new();
    for entry in std::fs::read_dir("src").expect("read src") {
        let text = std::fs::read_to_string(entry.unwrap().path()).expect("read source");
        for part in text.split("fn sailrv_").skip(1) {
            let rest: String = part.chars().take_while(|c| c.is_ascii_alphanumeric() || *c == '_').collect();
            if !rest.is_empty() {
                exports.push(format!("sailrv_{rest}"));
            }
        }
    }
    exports.sort();
    exports.dedup();
    let def = out.join("sailrv.def");
    std::fs::write(&def, format!("LIBRARY sailrv\nEXPORTS\n{}\n", exports.join("\n"))).expect("write sailrv.def");

    let target = env::var("TARGET").unwrap();
    let linker = cc::windows_registry::find_tool(&target, "link.exe").expect("MSVC link.exe not found");
    let dll = out.join("sailrv.dll");
    let mut args = vec![
        "/NOLOGO".to_string(),
        "/DLL".to_string(),
        format!("/OUT:{}", dll.display()),
        format!("/DEF:{}", def.display()),
        format!("/IMPLIB:{}", out.join("sailrv_dll.lib").display()),
    ];
    args.extend(libs.iter().map(|l| l.display().to_string()));
    if let Some(dir) = gmp_lib_dir {
        args.push(format!("/LIBPATH:{}", dir.display()));
    }
    if let Ok(dir) = env::var("ZLIB_LIB_DIR") {
        args.push(format!("/LIBPATH:{dir}"));
    }
    if system_gmp {
        args.push(format!("{}.lib", gmp_lib_name()));
    }
    if system_runtime {
        args.push(format!("{}.lib", zlib_lib_name("msvc")));
    }
    // Long paths can exceed the Windows command-line limit.
    let rsp = out.join("sailrv_link.rsp");
    std::fs::write(&rsp, args.iter().map(|a| format!("\"{a}\"\n")).collect::<String>()).expect("write link response file");
    let status = linker.to_command().arg(format!("@{}", rsp.display())).status().expect("run link.exe");
    assert!(status.success(), "linking {} failed", dll.display());

    if system_gmp && !gmp_static {
        if let Some(bin) = gmp_lib_dir.and_then(Path::parent).map(|p| p.join("bin")) {
            for entry in std::fs::read_dir(&bin).into_iter().flatten().flatten() {
                let name = entry.file_name().to_string_lossy().to_lowercase();
                if name.starts_with("gmp") && name.ends_with(".dll") {
                    std::fs::copy(entry.path(), out.join(entry.file_name())).expect("copy gmp DLL");
                }
            }
        }
    }

    println!("cargo:rustc-cfg=sailrv_dll");
    println!("cargo:rustc-env=SAILRV_DLL={}", dll.display());
}

fn emit_link_deps(gmp_lib_dir: Option<&Path>, system_gmp: bool, gmp_static: bool, system_runtime: bool, target_env: &str) {
    if let Some(dir) = gmp_lib_dir {
        println!("cargo:rustc-link-search=native={}", dir.display());
    }
    if let Ok(dir) = env::var("ZLIB_LIB_DIR") {
        println!("cargo:rustc-link-search=native={dir}");
    }
    if system_gmp {
        let kind = if gmp_static { "static=" } else { "" };
        println!("cargo:rustc-link-lib={kind}{}", gmp_lib_name());
    }
    if system_runtime {
        println!("cargo:rustc-link-lib={}", zlib_lib_name(target_env)); // external elf.c may use zlib
    }
}

/// Discovery already skips import libs, but an explicit GMP_DIR/GMP_LIB_DIR
/// bypasses it — verify the resolved archive really is static, else the
/// static link would silently still depend on gmp's DLL at runtime. If
/// the lib dir is unknown (relying on the toolchain default), it can't be
/// located to inspect, so this is best-effort.
fn check_static_gmp(gmp_lib_dir: Option<&Path>) {
    let gmp = gmp_lib_name();
    if let Some(dir) = gmp_lib_dir {
        for cand in [format!("{gmp}.lib"), format!("lib{gmp}.a")] {
            let p = dir.join(&cand);
            if p.is_file() && archive_is_static(&p) == Some(false) {
                panic!(
                    "system-gmp-static requested but {p:?} is a DLL import library, not \
                     a static archive — linking it would still need gmp's DLL at runtime. \
                     Point at a static libgmp (e.g. vcpkg x64-windows-static)."
                );
            }
        }
    }
}
