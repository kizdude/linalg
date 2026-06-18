/* vector.h - vector helpers built on the dynamic Mat type.
 *
 * A "vector" here is simply an Nx1 matrix, so all matrix routines apply. These
 * helpers add the operations that only make sense for vectors.
 */
#ifndef LINALG_VECTOR_H
#define LINALG_VECTOR_H

#include "matrix.h"

#ifndef LINALG_API
#  define LINALG_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Column vector (n x 1) from a plain array. */
LINALG_API Mat *vec_create(int n, const double *data);

/* Dot product of two vectors of equal length. Returns NAN on mismatch. */
LINALG_API double vec_dot(const Mat *a, const Mat *b);

/* Euclidean norm. */
LINALG_API double vec_norm(const Mat *a);

/* Unit vector (new matrix), or NULL if the vector is zero-length. */
LINALG_API Mat *vec_normalize(const Mat *a);

/* 3D cross product; both inputs must be length-3 vectors. NULL otherwise. */
LINALG_API Mat *vec_cross(const Mat *a, const Mat *b);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_VECTOR_H */
