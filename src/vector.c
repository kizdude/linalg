#include "linalg/linalg.h"

#include <stddef.h>
#include <math.h>

/* A "vector" is just an Nx1 (or 1xN) Mat, so you can lean on the matrix
 * routines. These stubs add the vector-only operations. */

Mat *vec_create(int n, const double *data) {
    /* TODO: an n x 1 column vector from data (hint: mat_from_array). */
    (void)n; (void)data;
    return NULL;
}

double vec_dot(const Mat *a, const Mat *b) {
    /* TODO: sum of products of corresponding components. Return NAN if the
     * lengths differ or either isn't a vector. */
    (void)a; (void)b;
    return NAN;
}

double vec_norm(const Mat *a) {
    /* TODO: sqrt of the dot product with itself. */
    (void)a;
    return NAN;
}

Mat *vec_normalize(const Mat *a) {
    /* TODO: a scaled by 1/norm; NULL if the norm is 0. */
    (void)a;
    return NULL;
}

Mat *vec_cross(const Mat *a, const Mat *b) {
    /* TODO: 3D cross product; NULL unless both are length-3 vectors. */
    (void)a; (void)b;
    return NULL;
}
