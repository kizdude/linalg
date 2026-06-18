#include "linalg/linalg.h"

#include <stdlib.h>
#include <math.h>

/* Decompositions and solvers. These are the hardest functions in the library;
 * we'll work through the algorithms together before you implement them. */

int mat_lu(const Mat *a, Mat **L, Mat **U, int *perm) {
    /* TODO: LU with partial pivoting, A = P^T L U.
     * Return 0 on success (allocate *L and *U), 2 if singular, 1 on bad args. */
    if (!a || !L || !U || !perm) return 1;
    int n = mat_rows(a);
    if (n != mat_cols(a)) return 1;

    *U = mat_copy(a);
    *L = mat_identity(n);
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }
    for (int k = 0; k < n; k++) {
        // Find pivot
        int pivot_row = k;
        double max_val = fabs(mat_get(*U, k, k));
        for (int i = k + 1; i < n; i++) {
            double val = fabs(mat_get(*U, i, k));
            if (val > max_val) {
                max_val = val;
                pivot_row = i;
            }
        }
        if (max_val == 0.0) {
            mat_free(*L);
            mat_free(*U);
            return 2; // Singular matrix
        }
        // Swap rows in U and L
        if (pivot_row != k) {
            // Swap rows in U
            for (int j = 0; j < n; j++) {
                double temp = mat_get(*U, k, j);
                mat_set(*U, k, j, mat_get(*U, pivot_row, j));
                mat_set(*U, pivot_row, j, temp);
            }
            // Swap rows in L (only the part before the diagonal)
            for (int j = 0; j < k; j++) {
                double temp = mat_get(*L, k, j);
                mat_set(*L, k, j, mat_get(*L, pivot_row, j));
                mat_set(*L, pivot_row, j, temp);
            }
            // Update permutation
            int temp = perm[k];
            perm[k] = perm[pivot_row];
            perm[pivot_row] = temp;
        }
        // Elimination
        for (int i = k + 1; i < n; i++) {
            double factor = mat_get(*U, i, k) / mat_get(*U, k, k);
            mat_set(*L, i, k, factor);
            for (int j = k; j < n; j++) {
                double new_val = mat_get(*U, i, j) - factor * mat_get(*U, k, j);
                mat_set(*U, i, j, new_val);
            }
        }
    }

    return 0;
}

double mat_determinant(const Mat *a) {
    int n = mat_rows(a);
    if (!a || n != mat_cols(a)) return NAN;

    Mat *L, *U;
    int *perm = malloc(n * sizeof(int));
    if (!perm) return NAN;
    int rc = mat_lu(a, &L, &U, perm);
    if (rc != 0) {
        free(perm);
        if (rc == 1) {
            mat_free(L);
            mat_free(U);
        }
        return NAN; // Singular or bad args
    }
    if (rc == 2) {
        free(perm);
        mat_free(L);
        mat_free(U);
        return 0.0; // Singular matrix
    }

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        det *= mat_get(U, i, i);
    }

    // pivot sign from perm parity
    int swaps = 0;
    int *seen = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        int len = 0;
        int j = i;
        while (!seen[j]) {
            seen[j] = 1;
            j = perm[j];
            len++;
        }
        if (len > 0) {
            swaps += len - 1;
        }
    }
    if (swaps % 2 != 0) {
        det = -det;
    }

    free(seen);
    free(perm);
    mat_free(L);
    mat_free(U);
    return det;
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
