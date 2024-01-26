#include "util.h"

void init_vec3(Vec3 *v, float x, float y, float z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

void add_vec3(Vec3 *a, const Vec3 *b) {
  a->x = a->x + b->x;
  a->y = a->y + b->y;
  a->z = a->z + b->z;
}

void sub_vec3(Vec3 *a, const Vec3 *b) {
  a->x = a->x - b->x;
  a->y = a->y - b->y;
  a->z = a->z - b->z;
}

void normalize_vec3(Vec3 *v) {
  float len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  if (len != 0) {
    v->x /= len;
    v->y /= len;
    v->z /= len;
  }
}

float deg_to_rad(float deg) { return deg * M_PI / 180.0f; }

void set_identity_mat(Mat4 *m) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      m->m[i][j] = (i == j) ? 1.0f : 0.0f;
    }
  }
}

void build_rotation(Mat4 *m, float rad, Axis axis) {
  set_identity_mat(m);

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

void build_translation(Mat4 *m, float x, float y, float z) {
  set_identity_mat(m);
  m->m[0][3] = x;
  m->m[1][3] = y;
  m->m[2][3] = z;
}

void build_scale(Mat4 *m, float x, float y, float z) {
  set_identity_mat(m);
  m->m[0][0] = x;
  m->m[1][1] = y;
  m->m[2][2] = z;
}