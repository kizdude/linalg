/* gfx.h - fixed-size graphics types and transforms (float, column-vector
 * convention with column-major Mat4 storage, matching OpenGL).
 *
 * These are plain-old-data structs passed by value for ergonomic C use. For
 * FFI safety (small-struct-by-value ABI differs across platforms) every
 * operation also has an out-parameter variant suffixed _out that takes/returns
 * pointers; Python bindings use those.
 */
#ifndef LINALG_GFX_H
#define LINALG_GFX_H

#ifndef LINALG_API
#  define LINALG_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { float x, y; }          Vec2;
typedef struct { float x, y, z; }       Vec3;
typedef struct { float x, y, z, w; }    Vec4;
/* Column-major 4x4: m[col*4 + row]. */
typedef struct { float m[16]; }         Mat4;
/* Quaternion (x,y,z imaginary, w real). */
typedef struct { float x, y, z, w; }    Quat;

/* --- Vec3 (by value) --- */
LINALG_API Vec3  vec3_add(Vec3 a, Vec3 b);
LINALG_API Vec3  vec3_sub(Vec3 a, Vec3 b);
LINALG_API Vec3  vec3_scale(Vec3 a, float s);
LINALG_API float vec3_dot(Vec3 a, Vec3 b);
LINALG_API Vec3  vec3_cross(Vec3 a, Vec3 b);
LINALG_API float vec3_length(Vec3 a);
LINALG_API Vec3  vec3_normalize(Vec3 a);

/* --- Mat4 (by value) --- */
LINALG_API Mat4  mat4_identity(void);
LINALG_API Mat4  mat4_mul(Mat4 a, Mat4 b);
LINALG_API Mat4  mat4_translate(float x, float y, float z);
LINALG_API Mat4  mat4_scale(float x, float y, float z);
LINALG_API Mat4  mat4_rotate_x(float radians);
LINALG_API Mat4  mat4_rotate_y(float radians);
LINALG_API Mat4  mat4_rotate_z(float radians);
LINALG_API Mat4  mat4_perspective(float fovy_radians, float aspect, float znear, float zfar);
LINALG_API Mat4  mat4_look_at(Vec3 eye, Vec3 center, Vec3 up);
LINALG_API Vec4  mat4_mul_vec4(Mat4 m, Vec4 v);

/* --- Quaternion --- */
LINALG_API Quat  quat_identity(void);
LINALG_API Quat  quat_from_axis_angle(Vec3 axis, float radians);
LINALG_API Quat  quat_mul(Quat a, Quat b);
LINALG_API Mat4  quat_to_mat4(Quat q);

/* --- FFI-safe pointer variants (no struct-by-value across the boundary) --- */
LINALG_API void mat4_identity_out(Mat4 *out);
LINALG_API void mat4_mul_out(const Mat4 *a, const Mat4 *b, Mat4 *out);
LINALG_API void mat4_mul_vec4_out(const Mat4 *m, const Vec4 *v, Vec4 *out);
LINALG_API void vec3_cross_out(const Vec3 *a, const Vec3 *b, Vec3 *out);

#ifdef __cplusplus
}
#endif

#endif /* LINALG_GFX_H */
