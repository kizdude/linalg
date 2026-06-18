#include "linalg/linalg.h"

#include <stdlib.h>
#include <math.h>

/* Decompositions and solvers. These are the hardest functions in the library;
 * we'll work through the algorithms together before you implement them. */

int mat_lu(const Mat *a, Mat **L, Mat **U, int *perm) {
    /* TODO: LU with partial pivoting, A = P^T L U.
     * Return 0 on success (allocate *L and *U), 2 if singular, 1 on bad args. */
    (void)a; (void)L; (void)U; (void)perm;
    return 1;
}

double mat_determinant(const Mat *a) {
    /* TODO: product of U's diagonal from the LU, times the pivot sign.
     * NAN if not square. */
    (void)a;
    return NAN;
}

Mat *mat_solve(const Mat *a, const Mat *b) {
    /* TODO: solve A x = b via LU (forward then back substitution). */
    (void)a; (void)b;
    return NULL;
}

Mat *mat_inverse(const Mat *a) {
    /* TODO: solve A X = I; NULL if singular / not square. */
    (void)a;
    return NULL;
}

int mat_qr(const Mat *a, Mat **Q, Mat **R) {
    /* TODO: QR via (modified) Gram-Schmidt, A = Q R.
     * Return 0 on success (allocate *Q and *R), nonzero on failure. */
    (void)a; (void)Q; (void)R;
    return 1;
}
