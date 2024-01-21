#include "util.h"

void init_vec3(Vec3 *v, float x, float y, float z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

Vec3 add_vec3(const Vec3 *a, const Vec3 *b) {
  Vec3 v;
  v.x = a->x + b->x;
  v.y = a->y + b->y;
  v.z = a->z + b->z;
  return v;
}

Vec3 sub_vec3(const Vec3 *a, const Vec3 *b) {
  Vec3 v;
  v.x = a->x - b->x;
  v.y = a->y - b->y;
  v.z = a->z - b->z;
  return v;
}

void normalize_vec3(Vec3 *v) {
  float len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  if (len != 0) {
    v->x /= len;
    v->y /= len;
    v->z /= len;
  }
}