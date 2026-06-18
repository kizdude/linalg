/* linalg.h - umbrella header for the linalg library.
 *
 * A hybrid linear algebra library:
 *   - a general dynamic NxM matrix/vector core (matrix.h, vector.h, decomp.h)
 *   - graphics-focused fixed-size types and transforms (gfx.h)
 *
 * The public API is annotated with LINALG_API so the same headers work for
 * building the shared library and for consuming it.
 */
#ifndef LINALG_H
#define LINALG_H

#if defined(_WIN32)
#  if defined(LINALG_BUILD)
#    define LINALG_API __declspec(dllexport)
#  else
#    define LINALG_API __declspec(dllimport)
#  endif
#else
#  if defined(LINALG_BUILD)
#    define LINALG_API __attribute__((visibility("default")))
#  else
#    define LINALG_API
#  endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "matrix.h"
#include "vector.h"
#include "decomp.h"
#include "gfx.h"

/* Returns a static version string, e.g. "0.1.0". */
LINALG_API const char *linalg_version(void);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_H */
