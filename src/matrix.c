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
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }
    Mat *m = malloc(sizeof(Mat));
    if (!m) return NULL;
    double *data = malloc((size_t)rows * cols * sizeof(double));
    if (!data) {
        free(m);
        return NULL;
    }
    m->rows = rows;
    m->cols = cols;
    m->data = data;
    return m;
}

Mat *mat_zeros(int rows, int cols) {
    Mat *m = mat_create(rows, cols);
    if (!m) return NULL;
    memset(m->data, 0, (size_t)rows * cols * sizeof(double));
    return m;
}

Mat *mat_identity(int n) {
    Mat *m = mat_zeros(n, n);
    if (!m) return NULL;
    for (int i = 0; i < n; i++) {
        m->data[i * n + i] = 1.0;
    }
    return m;
}

Mat *mat_from_array(int rows, int cols, const double *data) {
    if (!data) return NULL;
    Mat *m = mat_create(rows, cols);
    if (!m) return NULL;
    memcpy(m->data, data, (size_t)rows * cols * sizeof(double));
    return m;
}

Mat *mat_copy(const Mat *a) {
    if (!a) return NULL;
    Mat *m = mat_create(a->rows, a->cols);
    if (!m) return NULL;
    memcpy(m->data, a->data, (size_t)a->rows * a->cols * sizeof(double));
    return m;
}

void mat_free(Mat *m) {
    if (!m) return;
    free(m->data);
    free(m);
}

int mat_rows(const Mat *m) {
    if (!m) return 0;
    return m->rows;
}

int mat_cols(const Mat *m) {
    if (!m) return 0;
    return m->cols;
}

double mat_get(const Mat *m, int i, int j) {
    if (!m) return NAN;
    if (i < 0 || i >= m->rows || j < 0 || j >= m->cols) return NAN;
    return m->data[i * m->cols + j];
}

Mat *mat_get_col(const Mat *m, int j) {
    if (!m) return NULL;
    if (j < 0 || j >= m->cols) return NULL;
    Mat *col = mat_create(m->rows, 1);
    if (!col) return NULL;
    for (int i = 0; i < m->rows; i++) {
        col->data[i] = m->data[i * m->cols + j];
    }
    return col;
}

void mat_set(Mat *m, int i, int j, double v) {
    if (!m) return;
    if (i < 0 || i >= m->rows || j < 0 || j >= m->cols) return;
    m->data[i * m->cols + j] = v;
}

void mat_to_array(const Mat *m, double *out) {
    if (!m || !out) return;
    memcpy(out, m->data, (size_t)m->rows * m->cols * sizeof(double));
}

Mat *mat_add(const Mat *a, const Mat *b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Mat *result = mat_create(a->rows, a->cols);
    if (!result) return NULL;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i * a->cols + j] = a->data[i * a->cols + j] + b->data[i * b->cols + j];
        }
    }
    return result;
}

Mat *mat_sub(const Mat *a, const Mat *b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Mat *result = mat_create(a->rows, a->cols);
    if (!result) return NULL;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i * a->cols + j] = a->data[i * a->cols + j] - b->data[i * b->cols + j];
        }
    }
    return result;
}

Mat *mat_scale(const Mat *a, double s) {
    if (!a) return NULL;
    Mat *result = mat_create(a->rows, a->cols);
    if (!result) return NULL;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i * a->cols + j] = a->data[i * a->cols + j] * s;
        }
    }
    return result;
}

Mat *mat_mul(const Mat *a, const Mat *b) {
    if (!a || !b) return NULL;
    if (a->cols != b->rows) return NULL;
    Mat *result = mat_create(a->rows, b->cols);
    if (!result) return NULL;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < a->cols; k++) {
                sum += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
            result->data[i * b->cols + j] = sum;
        }
    }
    return result;
}

Mat *mat_transpose(const Mat *a) {
    if (!a) return NULL;
    Mat *result = mat_create(a->cols, a->rows);
    if (!result) return NULL;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[j * a->rows + i] = a->data[i * a->cols + j];
        }
    }
    return result;
}

int mat_equal(const Mat *a, const Mat *b, double tol) {
    if (!a || !b) return 0;
    if (a->rows != b->rows || a->cols != b->cols) return 0;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            double diff = fabs(a->data[i * a->cols + j] - b->data[i * b->cols + j]);
            if (!(diff <= tol)) return 0;
        }
    }
    return 1;
}

