/* decomp.h - decompositions and solvers for the dynamic Mat type. */
#ifndef LINALG_DECOMP_H
#define LINALG_DECOMP_H

#include "matrix.h"

#ifndef LINALG_API
#  define LINALG_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Determinant of a square matrix via LU. Returns NAN if not square. */
LINALG_API double mat_determinant(const Mat *a);

/* Inverse of a square matrix, or NULL if singular / not square. */
LINALG_API Mat *mat_inverse(const Mat *a);

/* Solve A x = b for a square A and column vector b. NULL on failure. */
LINALG_API Mat *mat_solve(const Mat *a, const Mat *b);

/* LU decomposition with partial pivoting: A = P^T * L * U.
 * On success returns 0 and fills *L, *U (caller frees both) and the pivot
 * permutation perm (length n, caller-allocated). Returns nonzero on failure. */
LINALG_API int mat_lu(const Mat *a, Mat **L, Mat **U, int *perm);

/* QR decomposition via Gram-Schmidt: A = Q * R, Q orthonormal columns.
 * Returns 0 on success (caller frees *Q and *R), nonzero on failure. */
LINALG_API int mat_qr(const Mat *a, Mat **Q, Mat **R);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_DECOMP_H */
