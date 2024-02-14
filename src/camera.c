#include "camera.h"

void camera_init(Camera *c, const Vec3 pos, const Vec3 target, const Vec3 up,
                 float fov, float near, float far) {
  c->pos = pos;

  c->dir = vec3_sub(target, pos);
  vec3_normalize(&c->dir);

  c->up = up;
  vec3_normalize(&c->up);

  c->fov = fov;
  c->near = near;
  c->far = far;
}

void camera_get_view_mat(const Camera *c, Mat4 *m) {
  Vec3 right = vec3_cross(c->dir, c->up);
  vec3_normalize(&right);
  Vec3 up = vec3_cross(right, c->dir);
  vec3_normalize(&up);

  m->m[0][0] = right.x;
  m->m[0][1] = right.y;
  m->m[0][2] = right.z;
  m->m[0][3] = -vec3_dot(right, c->pos);
  m->m[1][0] = up.x;
  m->m[1][1] = up.y;
  m->m[1][2] = up.z;
  m->m[1][3] = -vec3_dot(up, c->pos);
  m->m[2][0] = -c->dir.x;
  m->m[2][1] = -c->dir.y;
  m->m[2][2] = -c->dir.z;
  m->m[2][3] = vec3_dot(c->dir, c->pos);
  m->m[3][0] = 0.0f;
  m->m[3][1] = 0.0f;
  m->m[3][2] = 0.0f;
  m->m[3][3] = 1.0f;
}

void camera_get_proj_mat(const Camera *c, Mat4 *m, float aspect_ratio,
                         Projection p) {
  float f = 1.0f / tanf(c->fov / 2.0f);
  if (p == PERSPECTIVE) {
    m->m[0][0] = f / aspect_ratio;
    m->m[0][1] = 0.0f;
    m->m[0][2] = 0.0f;
    m->m[0][3] = 0.0f;

    m->m[1][0] = 0.0f;
    m->m[1][1] = f;
    m->m[1][2] = 0.0f;
    m->m[1][3] = 0.0f;

    m->m[2][0] = 0.0f;
    m->m[2][1] = 0.0f;
    m->m[2][2] = (c->far + c->near) / (c->far - c->near);
    m->m[2][3] = (2.0f * c->far * c->near) / (c->far - c->near);
    m->m[3][0] = 0.0f;
    m->m[3][1] = 0.0f;
    m->m[3][2] = -1.0f;
    m->m[3][3] = 0.0f;
  } else {
    m->m[0][0] = 0.0f;
    m->m[0][1] = 0.0f;
    m->m[0][2] = 0.0f;
    m->m[0][3] = 0.0f;
    m->m[1][0] = 0.0f;
    m->m[1][1] = 0.0f;
    m->m[1][2] = 0.0f;
    m->m[1][3] = 0.0f;
    m->m[2][0] = 0.0f;
    m->m[2][1] = 0.0f;
    m->m[2][2] = 0.0f;
    m->m[2][3] = 0.0f;
    m->m[3][0] = 0.0f;
  }
}