/* matrix.h - dynamic, heap-allocated NxM matrix of doubles.
 *
 * The Mat type is an opaque handle: callers never see its layout, which keeps
 * the ABI stable and makes the type trivial to wrap from ctypes (it is just a
 * pointer). Every constructor returns a heap object that the caller must free
 * with mat_free(). Functions that allocate return NULL on failure (bad
 * dimensions, out of memory); query functions return a sentinel (0 / NAN).
 */
#ifndef LINALG_MATRIX_H
#define LINALG_MATRIX_H

#ifndef LINALG_API
#  define LINALG_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Mat Mat;

/* --- lifecycle --- */
LINALG_API Mat  *mat_create(int rows, int cols);          /* uninitialised */
LINALG_API Mat  *mat_zeros(int rows, int cols);
LINALG_API Mat  *mat_identity(int n);
LINALG_API Mat  *mat_from_array(int rows, int cols, const double *data); /* row-major */
LINALG_API Mat  *mat_copy(const Mat *a);
LINALG_API void  mat_free(Mat *m);

/* --- introspection --- */
LINALG_API int    mat_rows(const Mat *m);
LINALG_API int    mat_cols(const Mat *m);
LINALG_API double mat_get(const Mat *m, int i, int j);
LINALG_API void   mat_set(Mat *m, int i, int j, double v);
/* Copies all rows*cols elements (row-major) into out. */
LINALG_API void   mat_to_array(const Mat *m, double *out);

/* --- element-wise / scalar ops (return a new matrix) --- */
LINALG_API Mat *mat_add(const Mat *a, const Mat *b);
LINALG_API Mat *mat_sub(const Mat *a, const Mat *b);
LINALG_API Mat *mat_scale(const Mat *a, double s);
LINALG_API Mat *mat_mul(const Mat *a, const Mat *b);       /* matrix product */
LINALG_API Mat *mat_transpose(const Mat *a);

/* --- comparison --- */
/* 1 if same shape and every element within tol, else 0. */
LINALG_API int mat_equal(const Mat *a, const Mat *b, double tol);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_MATRIX_H */
