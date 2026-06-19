#include "linalg/linalg.h"

#include <stddef.h>
#include <math.h>

/* A "vector" is just an Nx1 (or 1xN) Mat. */
static int vec_len(const Mat *v) {
    if (!v) return -1;
    int rows = mat_rows(v), cols = mat_cols(v);
    if (rows == 1) return cols;
    if (cols == 1) return rows;
    return -1;
}

static double vec_at(const Mat *v, int i) {
    return (mat_cols(v) == 1) ? mat_get(v, i, 0) : mat_get(v, 0, i);
}

Mat *vec_create(int n, const double *data) {
    if (n <= 0) return NULL;
    if (!data) return NULL;
    Mat *v = mat_from_array(n, 1, data);
    return v;
}

double vec_dot(const Mat *a, const Mat *b) {
    if (!a || !b) return NAN;
    int na = vec_len(a), nb = vec_len(b);
    if (na < 0 || na != nb) return NAN;
    double sum = 0.0;
    for (int i = 0; i < na; i++) {
        sum += vec_at(a, i) * vec_at(b, i);
    }
    return sum;
}

double vec_norm(const Mat *a) {
    if (!a) return NAN;
    int n = vec_len(a);
    if (n <= 0) return NAN;
    double dot_product = vec_dot(a, a);
    return sqrt(dot_product);
}

Mat *vec_normalize(const Mat *a) {
    if (!a) return NULL;
    int n = vec_len(a);
    if (n <= 0) return NULL;
    double norm = vec_norm(a);
    if (!(norm > 0)) return NULL;
    return mat_scale(a, 1.0 / norm);
}

Mat *vec_cross(const Mat *a, const Mat *b) {
    if (!a || !b) return NULL;
    int na = vec_len(a), nb = vec_len(b);
    if (na != 3 || nb != 3) return NULL;
    Mat *result = mat_create(3, 1);
    if (!result) return NULL;
    double a1 = vec_at(a, 0);
    double a2 = vec_at(a, 1);
    double a3 = vec_at(a, 2);
    double b1 = vec_at(b, 0);
    double b2 = vec_at(b, 1);
    double b3 = vec_at(b, 2);
    mat_set(result, 0, 0, a2 * b3 - a3 * b2);
    mat_set(result, 1, 0, a3 * b1 - a1 * b3);
    mat_set(result, 2, 0, a1 * b2 - a2 * b1);
    return result;
}
