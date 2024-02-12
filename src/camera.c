#include "camera.h"

void camera_init(Camera *c, Vec3 pos, Vec3 target, Vec3 up, float fov,
                 float near, float far) {
  c->pos = pos;
  vec3_sub(&target, &pos, &c->dir);
  vec3_normalize(&c->dir);

  c->up = up;
  vec3_normalize(&c->up);

  c->fov = fov;
  c->near = near;
  c->far = far;
}
