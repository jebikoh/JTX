#ifndef LIGHTS_H
#define LIGHTS_H

#include "util.h"

typedef struct {
    Vec3 dir;
} DirLight;

void dirlight_init(DirLight *l, float x, float y, float z);
void dirlight_init_vec3(DirLight *l, const Vec3 direction);
DirLight dirlight_new(float x, float y, float z);
DirLight dirlight_new_vec3(const Vec3 direction);
float dirlight_intensity(const DirLight *l, float x, float y, float z);
float dirlight_intensity_vec3(const DirLight *l, const Vec3 normal);

#endif // LIGHTS_H