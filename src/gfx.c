#include "linalg/linalg.h"

#include <math.h>

/* Fixed-size graphics math. Convention: column vectors, column-major Mat4
 * storage (m[col*4 + row]) to match OpenGL. */

/* ---------- Vec3 ---------- */
Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}
Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
Vec3 vec3_scale(Vec3 a, float s) {
    return (Vec3){a.x * s, a.y * s, a.z * s};
}
float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
float vec3_length(Vec3 a) {
    return sqrtf(vec3_dot(a, a));
}
Vec3 vec3_normalize(Vec3 a) {
    float len = vec3_length(a);
    if (len > 0.0f) {
        return vec3_scale(a, 1.0f / len);
    }
    return (Vec3){0, 0, 0};
}

/* ---------- Mat4 (column-major: m[col*4 + row]) ---------- */
Mat4 mat4_identity(void) {
    Mat4 r = {{0}};
    r.m[0] = 1.0f;
    r.m[5] = 1.0f;
    r.m[10] = 1.0f;
    r.m[15] = 1.0f;
    return r;
}
Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 r = {{0}};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += a.m[k * 4 + row] * b.m[col * 4 + k];
            }
            r.m[col * 4 + row] = sum;
        }
    }
    return r;
}
Mat4 mat4_translate(float x, float y, float z) {
    Mat4 r = mat4_identity();
    r.m[12] = x;
    r.m[13] = y;
    r.m[14] = z;
    return r; 
}
Mat4 mat4_scale(float x, float y, float z) {
    Mat4 r = mat4_identity();
    r.m[0] = x;
    r.m[5] = y;
    r.m[10] = z;
    return r;
}
Mat4 mat4_rotate_x(float a) {
    Mat4 r = {{0}};
    float c = cosf(a);
    float s = sinf(a);
    r.m[0] = 1.0f;
    r.m[5] = c;
    r.m[6] = s;
    r.m[9] = -s;
    r.m[10] = c;
    r.m[15] = 1.0f;
    return r;
}
Mat4 mat4_rotate_y(float a) {
    Mat4 r = {{0}};
    float c = cosf(a);
    float s = sinf(a);
    r.m[0] = c;
    r.m[2] = -s;
    r.m[5] = 1.0f;
    r.m[8] = s;
    r.m[10] = c;
    r.m[15] = 1.0f;
    return r;
}
Mat4 mat4_rotate_z(float a) {
    Mat4 r = {{0}};
    float c = cosf(a);
    float s = sinf(a);
    r.m[0] = c;
    r.m[1] = s;
    r.m[4] = -s;
    r.m[5] = c;
    r.m[10] = 1.0f;
    r.m[15] = 1.0f;
    return r;
}

Mat4 mat4_perspective(float fovy, float aspect, float znear, float zfar) {
    Mat4 r = {{0}};
    float f = 1.0f / tanf(fovy * 0.5f);
    r.m[0] = f / aspect;
    r.m[5] = f;
    r.m[10] = (zfar + znear) / (znear - zfar);
    r.m[11] = -1.0f;
    r.m[14] = (2.0f * zfar * znear) / (znear - zfar);
    return r;
}

Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up) {
    Vec3 f = vec3_normalize(vec3_sub(center, eye));
    Vec3 s = vec3_normalize(vec3_cross(f, up));
    Vec3 u = vec3_cross(s, f);
    Mat4 r = mat4_identity();
    r.m[0] = s.x;
    r.m[4] = s.y;
    r.m[8] = s.z;
    r.m[1] = u.x;
    r.m[5] = u.y;
    r.m[9] = u.z;
    r.m[2] = -f.x;
    r.m[6] = -f.y;
    r.m[10] = -f.z;
    r.m[12] = -vec3_dot(s, eye);
    r.m[13] = -vec3_dot(u, eye);
    r.m[14] = vec3_dot(f, eye);
    return r;
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v) {
    Vec4 r;
    r.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8]  * v.z + m.m[12] * v.w;
    r.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9]  * v.z + m.m[13] * v.w;
    r.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14] * v.w;
    r.w = m.m[3] * v.x + m.m[7] * v.y + m.m[11] * v.z + m.m[15] * v.w;
    return r;
}

/* ---------- Quaternion ---------- */
Quat quat_identity(void) {
    return (Quat){0, 0, 0, 1};
}
Quat quat_from_axis_angle(Vec3 axis, float radians) {
    Vec3 a = vec3_normalize(axis);
    float h = radians * 0.5f;
    float s = sinf(h);
    return (Quat){ a.x * s, a.y * s, a.z * s, cosf(h) };
}
Quat quat_mul(Quat a, Quat b) {
    return (Quat){
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
    };
}
Mat4 quat_to_mat4(Quat q) {
    Mat4 r = mat4_identity();
    float x=q.x, y=q.y, z=q.z, w=q.w;
    r.m[0] = 1 - 2*y*y - 2*z*z;
    r.m[1] = 2*x*y + 2*w*z;
    r.m[2] = 2*x*z - 2*w*y;

    r.m[4] = 2*x*y - 2*w*z;
    r.m[5] = 1 - 2*x*x - 2*z*z;
    r.m[6] = 2*y*z + 2*w*x;

    r.m[8] = 2*x*z + 2*w*y;
    r.m[9] = 2*y*z - 2*w*x;
    r.m[10] = 1 - 2*x*x - 2*y*y;
    return r;
} 

/* ---------- FFI-safe pointer variants ---------- */
void mat4_identity_out(Mat4 *out) {
    if (out) *out = mat4_identity();
}
void mat4_mul_out(const Mat4 *a, const Mat4 *b, Mat4 *out) {
    if (a && b && out) *out = mat4_mul(*a, *b);
}
void mat4_mul_vec4_out(const Mat4 *m, const Vec4 *v, Vec4 *out) {
    if (m && v && out) *out = mat4_mul_vec4(*m, *v);
}
void vec3_cross_out(const Vec3 *a, const Vec3 *b, Vec3 *out) {
    if (a && b && out) *out = vec3_cross(*a, *b);
}
