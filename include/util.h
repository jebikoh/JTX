#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <cblas.h>

typedef struct {
    float x, y, z;
} Vec3;

void vec3_init(Vec3 *v, float x, float y, float z);
void vec3_add(const Vec3 *v1, const Vec3 *v2, Vec3 *out);
void vec3_sub(const Vec3 *v1, const Vec3 *v2, Vec3 *out);
void vec3_cross(const Vec3 *v1, const Vec3 *v2, Vec3 *out);
void vec3_normalize(Vec3 *v);
float vec3_dot(const Vec3 *v1, const Vec3 *v2);

typedef enum {
    X = 0,
    Y = 1, 
    Z = 2
} Axis;

typedef struct {
    float m[4][4];
} Mat4;

/**
 * @brief Converts degrees to radians
 * 
 * @param deg Degrees
 * @return float Radians
 */
float deg_to_rad(float deg);

/**
 * @brief Builds a 4x4 identity matrix
 * 
 * @param m Pointer to output matrix
 */
void build_identity(Mat4 *m);

/**
 * @brief Builds a 4x4 rotation matrix
 * 
 * @param m Pointer to output matrix
 * @param rad Rotation in radians
 * @param axis Axis of rotation
 */
void build_rmat(Mat4 *m, float rad, Axis axis);

/**
 * @brief Builds a 4x4 translation matrix
 *
 * @param m Pointer to output matrix
 * @param x Translation in x
 * @param y Translation in y
 * @param z Translation in z
 */
void build_tmat(Mat4 *m, float x, float y, float z);

/**
 * @brief Builds a 4x4 scale matrix
 * 
 * @param m Pointer to output matrix
 * @param x Scale in x
 * @param y Scale in y
 * @param z Scale in z
 */
void build_smat(Mat4 *m, float x, float y, float z);

/**
 * @brief Multiplies two 4x4 matrices
 * 
 * @param m1 Pointer to left matrix
 * @param m2 Poitner to right matrix
 * @param out Pointer to output matrix
 */
void mult_mat4(const Mat4 *m1, const Mat4 *m2, Mat4 *out);

/**
 * @brief Condenses multiple 4x4 matrices into one
 * 
 * @param m Array of matrices
 * @param n Number of matrices
 * @param out Pointer to output matrix
 */
void cond_mat4(const Mat4 *m, int n, Mat4 *out);

#endif // UTIL_H