#include "lights.h"

void dirlight_init(DirLight *l, float x, float y, float z) {
  l->dir = vec3_new(x, y, z);
  vec3_normalize(&l->dir);
}

void dirlight_init_vec3(DirLight *l, const Vec3 dir) {
  l->dir = dir;
  vec3_normalize(&l->dir);
}

DirLight dirlight_new(float x, float y, float z) {
  DirLight l;
  dirlight_init(&l, x, y, z);
  return l;
}

DirLight dirlight_new_vec3(const Vec3 dir) {
  DirLight l;
  dirlight_init_vec3(&l, dir);
  return l;
}

float dirlight_intensity(const DirLight *l, float x, float y, float z) {
  return fmax(0.0f, -vec3_dot_f(l->dir, x, y, z));
}

float dirlight_intensity_vec3(const DirLight *l, const Vec3 normal) {
  return fmax(0.0f, -vec3_dot(normal, l->dir));
}