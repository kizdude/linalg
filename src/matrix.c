#include "linalg/linalg.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Dense, row-major storage. Element (i,j) lives at data[i*cols + j].
 * You may change this layout if you implement everything consistently, but
 * row-major keeps mat_from_array / mat_to_array a straight memcpy. */
struct Mat {
    int rows;
    int cols;
    double *data; /* length rows*cols */
};

const char *linalg_version(void) { return "0.1.0"; }

/* ============================================================================
 * Each body below is a stub. Implement them one at a time; run the tests
 * (ctest) to check your work. Contracts are documented in include/linalg/.
 * Reminder: constructors return NULL on bad args / OOM; query functions
 * return a sentinel (NAN / 0) rather than crashing.
 * ==========================================================================*/

Mat *mat_create(int rows, int cols) {
    /* TODO: validate rows/cols > 0; malloc the Mat and its rows*cols data
     * buffer (uninitialised is fine here). Free partial allocations on
     * failure and return NULL. */
    (void)rows; (void)cols;
    return NULL;
}

Mat *mat_zeros(int rows, int cols) {
    /* TODO: mat_create then zero the buffer (memset or loop). */
    (void)rows; (void)cols;
    return NULL;
}

Mat *mat_identity(int n) {
    /* TODO: n x n zeros with 1.0 on the diagonal. */
    (void)n;
    return NULL;
}

Mat *mat_from_array(int rows, int cols, const double *data) {
    /* TODO: mat_create then memcpy rows*cols doubles from data (row-major). */
    (void)rows; (void)cols; (void)data;
    return NULL;
}

Mat *mat_copy(const Mat *a) {
    /* TODO: build a new matrix with the same shape and contents as a. */
    (void)a;
    return NULL;
}

void mat_free(Mat *m) {
    /* TODO: free m->data then m (guard against NULL). */
    (void)m;
}

int mat_rows(const Mat *m) {
    /* TODO */
    (void)m;
    return 0;
}

int mat_cols(const Mat *m) {
    /* TODO */
    (void)m;
    return 0;
}

double mat_get(const Mat *m, int i, int j) {
    /* TODO: bounds-check; return NAN if out of range, else element (i,j). */
    (void)m; (void)i; (void)j;
    return NAN;
}

void mat_set(Mat *m, int i, int j, double v) {
    /* TODO: bounds-check; write element (i,j). */
    (void)m; (void)i; (void)j; (void)v;
}

void mat_to_array(const Mat *m, double *out) {
    /* TODO: copy rows*cols elements (row-major) into out. */
    (void)m; (void)out;
}

Mat *mat_add(const Mat *a, const Mat *b) {
    /* TODO: shape-check, then element-wise sum into a new matrix. */
    (void)a; (void)b;
    return NULL;
}

Mat *mat_sub(const Mat *a, const Mat *b) {
    /* TODO: element-wise a - b. */
    (void)a; (void)b;
    return NULL;
}

Mat *mat_scale(const Mat *a, double s) {
    /* TODO: multiply every element by s into a new matrix. */
    (void)a; (void)s;
    return NULL;
}

Mat *mat_mul(const Mat *a, const Mat *b) {
    /* TODO: matrix product. Requires a->cols == b->rows; result is
     * a->rows x b->cols. Start the result at zero and accumulate. */
    (void)a; (void)b;
    return NULL;
}

Mat *mat_transpose(const Mat *a) {
    /* TODO: result (i,j) = a (j,i). */
    (void)a;
    return NULL;
}

int mat_equal(const Mat *a, const Mat *b, double tol) {
    /* TODO: 1 if same shape and every |a-b| <= tol, else 0. */
    (void)a; (void)b; (void)tol;
    return 0;
}
