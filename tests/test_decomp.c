#include "linalg/linalg.h"
#include "test_util.h"

int main(void) {
    TEST_BEGIN();

    /* A = [[4,3],[6,3]], det = 4*3 - 3*6 = -6 */
    double av[4] = {4, 3, 6, 3};
    Mat *A = mat_from_array(2, 2, av);
    CHECK_NEAR(mat_determinant(A), -6.0, 1e-9, "determinant 2x2");

    /* 3x3 determinant */
    double bv[9] = {6, 1, 1, 4, -2, 5, 2, 8, 7};
    Mat *B = mat_from_array(3, 3, bv);
    CHECK_NEAR(mat_determinant(B), -306.0, 1e-6, "determinant 3x3");

    /* inverse: A * A^-1 == I */
    Mat *Ainv = mat_inverse(A);
    CHECK(Ainv != NULL, "inverse exists");
    Mat *prod = mat_mul(A, Ainv);
    Mat *I = mat_identity(2);
    CHECK(mat_equal(prod, I, 1e-9), "A * A^-1 == I");

    /* solve A x = b for x; verify A x == b */
    double rhs[2] = {10, 12};
    Mat *bb = mat_from_array(2, 1, rhs);
    Mat *x = mat_solve(A, bb);
    CHECK(x != NULL, "solve returns a solution");
    Mat *check = mat_mul(A, x);
    CHECK(mat_equal(check, bb, 1e-9), "A x == b");

    /* singular matrix: determinant 0, inverse NULL */
    double sv[4] = {1, 2, 2, 4};
    Mat *S = mat_from_array(2, 2, sv);
    CHECK_NEAR(mat_determinant(S), 0.0, 1e-9, "singular det == 0");
    CHECK(mat_inverse(S) == NULL, "singular inverse -> NULL");

    /* QR: Q*R == A, and Q^T Q == I */
    Mat *Q = NULL, *R = NULL;
    CHECK(mat_qr(B, &Q, &R) == 0, "qr succeeds");
    Mat *QR = mat_mul(Q, R);
    CHECK(mat_equal(QR, B, 1e-6), "Q R == A");
    Mat *Qt = mat_transpose(Q);
    Mat *QtQ = mat_mul(Qt, Q);
    Mat *I3 = mat_identity(3);
    CHECK(mat_equal(QtQ, I3, 1e-6), "Q^T Q == I (orthonormal)");

    mat_free(A); mat_free(B); mat_free(Ainv); mat_free(prod); mat_free(I);
    mat_free(bb); mat_free(x); mat_free(check); mat_free(S);
    mat_free(Q); mat_free(R); mat_free(QR); mat_free(Qt); mat_free(QtQ); mat_free(I3);

    return TEST_END();
}
