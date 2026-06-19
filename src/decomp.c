#include "linalg/linalg.h"

#include <stdlib.h>
#include <math.h>

/* Decompositions and solvers. These are the hardest functions in the library;
 * we'll work through the algorithms together before you implement them. */

double mat_norm(const Mat *a) {
    if (!a) return NAN;
    double sum = 0.0;
    int n = mat_rows(a);
    int m = mat_cols(a);
    for (int i = 0; i < n * m; i++) {
        sum += mat_get(a, i / m, i % m) * mat_get(a, i / m, i % m);
    }
    return sqrt(sum);
}

double mat_dot(const Mat *a, const Mat *b, int col) {
    if (!a || !b) return NAN;
    if (mat_rows(a) != mat_rows(b)) return NAN;
    if (col < 0 || col >= mat_cols(a)) return NAN;
    double sum = 0.0;
    int n = mat_rows(a);
    for (int i = 0; i < n; i++) {
        sum += mat_get(a, i, col) * mat_get(b, i, 0);
    }
    return sum;
}

int mat_lu(const Mat *a, Mat **L, Mat **U, int *perm) {
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
    if (rc == 2) {
        free(perm);
        return 0.0; // Singular matrix
    }
    if (rc != 0) {
        free(perm);
        return NAN; // bad args
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

static Mat *lu_solve(const Mat *a, const Mat *b) {
    int n = mat_rows(a);
    if (n != mat_cols(a) || n != mat_rows(b)) {
        return NULL; // bad args
    }
    int nrhs = mat_cols(b);

    Mat *L, *U;
    int *perm = malloc(n * sizeof(int));
    if (!perm) return NULL;
    if (mat_lu(a, &L, &U, perm) != 0) {
        free(perm);
        return NULL; // singular or bad args
    }
     
    Mat *x = mat_create(n, nrhs);
    if (!x) {
        mat_free(L);
        mat_free(U);
        free(perm);
        return NULL; // allocation failure
    }
    double *y = malloc(n * sizeof(double));
    if (!y) {
        mat_free(L);
        mat_free(U);
        mat_free(x);
        free(perm);
        return NULL; // allocation failure
    }

    for (int col = 0; col < nrhs; col++) {
        // Forward substitution to solve L y = P b
        for (int i = 0; i < n; i++) {
            double sum = mat_get(b, perm[i], col);
            for (int j = 0; j < i; j++) {
                sum -= mat_get(L, i, j) * y[j];
            }
            y[i] = sum;
        }
        // Back substitution to solve U x = y
        for (int i = n - 1; i >= 0; i--) {
            double sum = y[i];
            for (int j = i + 1; j < n; j++) {
                sum -= mat_get(U, i, j) * mat_get(x, j, col);
            }
            mat_set(x, i, col, sum / mat_get(U, i, i));
        }
    }
    free(y);
    free(perm);
    mat_free(L);
    mat_free(U);
    return x;
}

Mat *mat_solve(const Mat *a, const Mat *b) {
    return lu_solve(a, b);
}

Mat *mat_inverse(const Mat *a) {
    int n  = mat_rows(a);
    if (n != mat_cols(a)) return NULL; // bad args
    Mat *I = mat_identity(n);
    if (!I) return NULL;
    Mat *inv = lu_solve(a, I);
    if (!inv) {
        mat_free(I);
        return NULL; // singular or allocation failure
    }
    mat_free(I);
    return inv;
}

int mat_qr(const Mat *a, Mat **Q, Mat **R) {
    /* TODO: QR via (modified) Gram-Schmidt, A = Q R.
     * Return 0 on success (allocate *Q and *R), nonzero on failure. */
    if (!a || !Q || !R) return 1;
    int m = mat_rows(a);
    int n = mat_cols(a);
    if (m < n) return 1; // not enough rows for QR
    *Q = mat_zeros(m, n);
    *R = mat_zeros(n, n);
    if (!*Q || !*R) {
        mat_free(*Q);
        mat_free(*R);
        return 1; // allocation failure
    }

    for (int j = 0; j < n; j++) {
        Mat *v = mat_get_col(a, j);
        if (!v) {
            mat_free(*Q);
            mat_free(*R);
            return 1; // allocation failure
        }
        for (int k = 0; k < j; k++) { // remove projections onto previous q_k
            double dot = mat_dot(*Q, v, k); // q_k . v
            mat_set(*R, k, j, dot);
            for (int i = 0; i < m; i++) {
                double val = mat_get(v, i, 0) - dot * mat_get(*Q, i, k);
                mat_set(v, i, 0, val);
            }
        }

        double norm = mat_norm(v);

        mat_set(*R, j, j, norm);
        if (norm == 0) {
            mat_free(v);
            mat_free(*Q);
            mat_free(*R);
            return 2; // singular matrix, cannot compute QR
        }
        for (int i = 0; i < m; i++) {
            mat_set(*Q, i, j, mat_get(v, i, 0) / norm);
        }
        mat_free(v);
    }
    return 0;
}
