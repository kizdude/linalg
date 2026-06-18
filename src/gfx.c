#include "linalg/linalg.h"

#include <math.h>

/* Fixed-size graphics math. Convention: column vectors, column-major Mat4
 * storage (m[col*4 + row]) to match OpenGL. Implement these as we get to them.
 *
 * The _out pointer variants at the bottom should just forward to the
 * by-value versions once those work. */

/* ---------- Vec3 ---------- */
Vec3 vec3_add(Vec3 a, Vec3 b)    { (void)a; (void)b; return (Vec3){0, 0, 0}; }   /* TODO */
Vec3 vec3_sub(Vec3 a, Vec3 b)    { (void)a; (void)b; return (Vec3){0, 0, 0}; }   /* TODO */
Vec3 vec3_scale(Vec3 a, float s) { (void)a; (void)s; return (Vec3){0, 0, 0}; }   /* TODO */
float vec3_dot(Vec3 a, Vec3 b)   { (void)a; (void)b; return 0.0f; }              /* TODO */
Vec3 vec3_cross(Vec3 a, Vec3 b)  { (void)a; (void)b; return (Vec3){0, 0, 0}; }   /* TODO */
float vec3_length(Vec3 a)        { (void)a; return 0.0f; }                       /* TODO */
Vec3 vec3_normalize(Vec3 a)      { (void)a; return (Vec3){0, 0, 0}; }            /* TODO */

/* ---------- Mat4 (column-major: m[col*4 + row]) ---------- */
Mat4 mat4_identity(void)         { Mat4 r = {{0}}; return r; }                   /* TODO */
Mat4 mat4_mul(Mat4 a, Mat4 b)    { (void)a; (void)b; Mat4 r = {{0}}; return r; } /* TODO */
Mat4 mat4_translate(float x, float y, float z) { (void)x; (void)y; (void)z; Mat4 r = {{0}}; return r; } /* TODO */
Mat4 mat4_scale(float x, float y, float z)     { (void)x; (void)y; (void)z; Mat4 r = {{0}}; return r; } /* TODO */
Mat4 mat4_rotate_x(float a)      { (void)a; Mat4 r = {{0}}; return r; }          /* TODO */
Mat4 mat4_rotate_y(float a)      { (void)a; Mat4 r = {{0}}; return r; }          /* TODO */
Mat4 mat4_rotate_z(float a)      { (void)a; Mat4 r = {{0}}; return r; }          /* TODO */

Mat4 mat4_perspective(float fovy, float aspect, float znear, float zfar) {
    (void)fovy; (void)aspect; (void)znear; (void)zfar;
    Mat4 r = {{0}};
    return r; /* TODO */
}

Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up) {
    (void)eye; (void)center; (void)up;
    Mat4 r = {{0}};
    return r; /* TODO */
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v) {
    (void)m; (void)v;
    return (Vec4){0, 0, 0, 0}; /* TODO */
}

/* ---------- Quaternion ---------- */
Quat quat_identity(void)         { return (Quat){0, 0, 0, 0}; }                  /* TODO */
Quat quat_from_axis_angle(Vec3 axis, float radians) { (void)axis; (void)radians; return (Quat){0, 0, 0, 0}; } /* TODO */
Quat quat_mul(Quat a, Quat b)    { (void)a; (void)b; return (Quat){0, 0, 0, 0}; } /* TODO */
Mat4 quat_to_mat4(Quat q)        { (void)q; Mat4 r = {{0}}; return r; }          /* TODO */

/* ---------- FFI-safe pointer variants (forward to the above) ---------- */
void mat4_identity_out(Mat4 *out) {
    /* TODO: if (out) *out = mat4_identity(); */
    (void)out;
}
void mat4_mul_out(const Mat4 *a, const Mat4 *b, Mat4 *out) {
    /* TODO */
    (void)a; (void)b; (void)out;
}
void mat4_mul_vec4_out(const Mat4 *m, const Vec4 *v, Vec4 *out) {
    /* TODO */
    (void)m; (void)v; (void)out;
}
void vec3_cross_out(const Vec3 *a, const Vec3 *b, Vec3 *out) {
    /* TODO */
    (void)a; (void)b; (void)out;
}
