#include "linalg/linalg.h"
#include "test_util.h"

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void) {
    TEST_BEGIN();

    /* Vec3 basics */
    Vec3 a = {1, 2, 2};
    Vec3 b = {3, 0, 4};
    Vec3 s = vec3_add(a, b);
    CHECK_NEAR(s.x, 4.0, 1e-6, "vec3_add.x");
    CHECK_NEAR(vec3_dot(a, b), 11.0, 1e-6, "vec3_dot");
    CHECK_NEAR(vec3_length(a), 3.0, 1e-6, "vec3_length");
    Vec3 n = vec3_normalize(a);
    CHECK_NEAR(vec3_length(n), 1.0, 1e-6, "normalized length 1");

    /* x cross y = z */
    Vec3 x = {1, 0, 0}, y = {0, 1, 0};
    Vec3 c = vec3_cross(x, y);
    CHECK_NEAR(c.z, 1.0, 1e-6, "cross z == 1");

    /* identity * v == v */
    Mat4 I = mat4_identity();
    Vec4 v = {1, 2, 3, 1};
    Vec4 iv = mat4_mul_vec4(I, v);
    CHECK_NEAR(iv.x, 1.0, 1e-6, "I*v keeps x");
    CHECK_NEAR(iv.z, 3.0, 1e-6, "I*v keeps z");

    /* translation moves a point */
    Mat4 T = mat4_translate(5, 0, 0);
    Vec4 tv = mat4_mul_vec4(T, v);
    CHECK_NEAR(tv.x, 6.0, 1e-6, "translate adds to x");

    /* scale */
    Mat4 S = mat4_scale(2, 3, 4);
    Vec4 sv = mat4_mul_vec4(S, v);
    CHECK_NEAR(sv.y, 6.0, 1e-6, "scale y by 3");

    /* rotate_z by 90deg sends +x to +y */
    Mat4 Rz = mat4_rotate_z((float)M_PI / 2.0f);
    Vec4 px = {1, 0, 0, 1};
    Vec4 rp = mat4_mul_vec4(Rz, px);
    CHECK_NEAR(rp.x, 0.0, 1e-5, "rotate_z 90: x->0");
    CHECK_NEAR(rp.y, 1.0, 1e-5, "rotate_z 90: y->1");

    /* composition: translate-then-scale via matrix product applied to v.
     * Result should equal applying each in the right order. */
    Mat4 TS = mat4_mul(T, S);          /* first scale, then translate */
    Vec4 r1 = mat4_mul_vec4(TS, v);
    Vec4 r2 = mat4_mul_vec4(T, mat4_mul_vec4(S, v));
    CHECK_NEAR(r1.x, r2.x, 1e-5, "mat4_mul matches sequential apply (x)");
    CHECK_NEAR(r1.y, r2.y, 1e-5, "mat4_mul matches sequential apply (y)");

    /* out-param variant agrees with by-value */
    Mat4 Io; mat4_identity_out(&Io);
    CHECK_NEAR(Io.m[0], 1.0, 1e-6, "identity_out diagonal");
    CHECK_NEAR(Io.m[1], 0.0, 1e-6, "identity_out off-diagonal");

    /* quaternion: 90deg about z, applied to +x, gives +y */
    Quat q = quat_from_axis_angle((Vec3){0, 0, 1}, (float)M_PI / 2.0f);
    Mat4 qm = quat_to_mat4(q);
    Vec4 qr = mat4_mul_vec4(qm, px);
    CHECK_NEAR(qr.y, 1.0, 1e-5, "quat rotate 90 about z: y->1");

    return TEST_END();
}
