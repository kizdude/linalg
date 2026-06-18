#include "linalg/linalg.h"
#include "test_util.h"

int main(void) {
    TEST_BEGIN();

    /* construction + introspection */
    Mat *z = mat_zeros(2, 3);
    CHECK(z != NULL, "mat_zeros returns non-NULL");
    CHECK(mat_rows(z) == 2, "rows == 2");
    CHECK(mat_cols(z) == 3, "cols == 3");
    CHECK_NEAR(mat_get(z, 1, 2), 0.0, 1e-12, "zeros are zero");
    mat_set(z, 1, 2, 5.0);
    CHECK_NEAR(mat_get(z, 1, 2), 5.0, 1e-12, "set/get round-trips");
    mat_free(z);

    /* out-of-range access returns NAN, not a crash */
    Mat *one = mat_zeros(1, 1);
    CHECK(isnan(mat_get(one, 3, 3)), "out-of-range get is NAN");
    mat_free(one);

    /* identity */
    Mat *id = mat_identity(3);
    CHECK_NEAR(mat_get(id, 0, 0), 1.0, 1e-12, "I diagonal");
    CHECK_NEAR(mat_get(id, 0, 1), 0.0, 1e-12, "I off-diagonal");

    /* from_array / to_array round-trip (row-major) */
    double vals[6] = {1, 2, 3, 4, 5, 6};
    Mat *a = mat_from_array(2, 3, vals);
    double out[6] = {0};
    mat_to_array(a, out);
    CHECK_NEAR(out[4], 5.0, 1e-12, "to_array preserves order");

    /* add / sub / scale */
    Mat *b = mat_from_array(2, 3, vals);
    Mat *sum = mat_add(a, b);
    CHECK_NEAR(mat_get(sum, 0, 0), 2.0, 1e-12, "add");
    Mat *diff = mat_sub(a, b);
    CHECK_NEAR(mat_get(diff, 1, 1), 0.0, 1e-12, "sub");
    Mat *sc = mat_scale(a, 2.0);
    CHECK_NEAR(mat_get(sc, 1, 2), 12.0, 1e-12, "scale");
    CHECK(mat_add(a, id) == NULL, "add with shape mismatch -> NULL");

    /* transpose */
    Mat *t = mat_transpose(a);          /* 3x2 */
    CHECK(mat_rows(t) == 3 && mat_cols(t) == 2, "transpose shape");
    CHECK_NEAR(mat_get(t, 2, 0), 3.0, 1e-12, "transpose element");

    /* multiply: (2x3)(3x2) = 2x2 */
    Mat *p = mat_mul(a, t);
    CHECK(mat_rows(p) == 2 && mat_cols(p) == 2, "mul shape");
    /* row0.row0 = 1*1+2*2+3*3 = 14 */
    CHECK_NEAR(mat_get(p, 0, 0), 14.0, 1e-12, "mul value");
    CHECK(mat_mul(a, b) == NULL, "mul with bad inner dim -> NULL");

    /* I * a == a */
    Mat *id2 = mat_identity(2);
    Mat *ia = mat_mul(id2, a);
    CHECK(mat_equal(ia, a, 1e-12), "I * a == a");

    mat_free(a); mat_free(b); mat_free(sum); mat_free(diff); mat_free(sc);
    mat_free(t); mat_free(p); mat_free(id); mat_free(id2); mat_free(ia);

    return TEST_END();
}
