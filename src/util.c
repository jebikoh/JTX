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