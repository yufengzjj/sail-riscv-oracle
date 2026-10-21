/* SoftFloat platform header for this crate's build (replaces the per-platform
 * build/<target>/platform.h; upstream's Linux-x86_64-GCC one is kept as
 * platform.upstream.h). GCC/Clang get the builtin clz and __int128 fast
 * paths like upstream; other compilers (MSVC) use SoftFloat's portable C. */

#define LITTLEENDIAN 1

#define INLINE static inline

#if defined(__GNUC__) || defined(__clang__)
#define SOFTFLOAT_BUILTIN_CLZ 1
#if defined(__SIZEOF_INT128__)
#define SOFTFLOAT_INTRINSIC_INT128 1
#endif
#include "opts-GCC.h"
#endif
