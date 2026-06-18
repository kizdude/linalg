#include "linalg/linalg.h"
#include "test_util.h"

int main(void) {
    TEST_BEGIN();

    double av[3] = {1, 2, 2};   /* length 3 */
    double bv[3] = {3, 0, 4};   /* length 5 */
    Mat *a = vec_create(3, av);
    Mat *b = vec_create(3, bv);
    CHECK(mat_rows(a) == 3 && mat_cols(a) == 1, "vec_create makes a column vector");

    CHECK_NEAR(vec_dot(a, b), 1*3 + 2*0 + 2*4, 1e-12, "dot product");
    CHECK_NEAR(vec_norm(a), 3.0, 1e-12, "norm of (1,2,2) is 3");

    Mat *u = vec_normalize(a);
    CHECK_NEAR(vec_norm(u), 1.0, 1e-12, "normalized vector has unit length");

    /* cross product: x cross y = z */
    double xv[3] = {1, 0, 0};
    double yv[3] = {0, 1, 0};
    Mat *x = vec_create(3, xv);
    Mat *y = vec_create(3, yv);
    Mat *c = vec_cross(x, y);
    CHECK(c != NULL, "cross of two 3-vectors is non-NULL");
    CHECK_NEAR(mat_get(c, 0, 0), 0.0, 1e-12, "cross.x");
    CHECK_NEAR(mat_get(c, 1, 0), 0.0, 1e-12, "cross.y");
    CHECK_NEAR(mat_get(c, 2, 0), 1.0, 1e-12, "cross.z == 1");

    /* zero vector cannot be normalized */
    double zv[3] = {0, 0, 0};
    Mat *zero = vec_create(3, zv);
    CHECK(vec_normalize(zero) == NULL, "normalizing zero -> NULL");

    mat_free(a); mat_free(b); mat_free(u);
    mat_free(x); mat_free(y); mat_free(c); mat_free(zero);

    return TEST_END();
}
