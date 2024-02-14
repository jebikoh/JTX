#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"

#include <math.h>

typedef enum {
    PERSPECTIVE = 0,
    ORTHOGRAPHIC = 1
} Projection;

typedef struct {
    Vec3 pos;
    Vec3 dir;
    Vec3 up;
    float fov;
    float near;
    float far;
} Camera;

void camera_init(Camera *c, Vec3 pos, Vec3 target, Vec3 up, float fov, float near, float far);
void camera_get_view_mat(const Camera *c, Mat4 *m);
void camera_get_proj_mat(const Camera *c, Mat4 *m, float aspect_ratio, Projection p);

#endif // MODEL_H