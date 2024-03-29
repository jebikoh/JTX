#include "util.h"

#include <string.h>

void vec3_init(Vec3 *v, float x, float y, float z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

Vec3 vec3_new(float x, float y, float z) { return (Vec3){x, y, z}; }

Vec3 vec3_add(const Vec3 a, const Vec3 b) {
  return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 vec3_sub(const Vec3 a, const Vec3 b) {
  return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 vec3_cross(const Vec3 a, const Vec3 b) {
  return (Vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x};
}

float vec3_dot(const Vec3 a, const Vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_dot_f(const Vec3 v, float x, float y, float z) {
  return v.x * x + v.y * y + v.z * z;
}

void vec3_normalize(Vec3 *v) {
  float len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  if (len != 0) {
    v->x /= len;
    v->y /= len;
    v->z /= len;
  }
}

float deg_to_rad(float deg) { return deg * M_PI / 180.0f; }

void build_identity(Mat4 *m) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      m->m[i][j] = (i == j) ? 1.0f : 0.0f;
    }
  }
}

void build_rmat(Mat4 *m, float rad, Axis axis) {
  build_identity(m);

  float c = cosf(rad);
  float s = sinf(rad);

  switch (axis) {
    case X:
      m->m[1][1] = c;
      m->m[1][2] = -s;
      m->m[2][1] = s;
      m->m[2][2] = c;
      break;
    case Y:
      m->m[0][0] = c;
      m->m[0][2] = s;
      m->m[2][0] = -s;
      m->m[2][2] = c;
      break;
    case Z:
      m->m[0][0] = c;
      m->m[0][1] = -s;
      m->m[1][0] = s;
      m->m[1][1] = c;
      break;
  }
}

void build_tmat(Mat4 *m, float x, float y, float z) {
  build_identity(m);
  m->m[0][3] = x;
  m->m[1][3] = y;
  m->m[2][3] = z;
}

void build_smat(Mat4 *m, float x, float y, float z) {
  build_identity(m);
  m->m[0][0] = x;
  m->m[1][1] = y;
  m->m[2][2] = z;
}

void mult_mat4(const Mat4 *m1, const Mat4 *m2, Mat4 *out) {
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 4, 4, 4, 1.0f,
              (float *)m1->m, 4, (float *)m2->m, 4, 0.0f, (float *)out->m, 4);
}

void cond_mat4(const Mat4 *m, int n, Mat4 *out) {
  build_identity(out);

  Mat4 tmp;
  for (int i = 0; i < n; i++) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 4, 4, 4, 1.0f,
                (float *)out->m, 4, (float *)m[i].m, 4, 0.0f, (float *)tmp.m,
                4);
    memcpy(out, &tmp, sizeof(Mat4));
  }
}