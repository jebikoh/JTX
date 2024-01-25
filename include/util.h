#ifndef UTIL_H
#define UTIL_H

#include <math.h>

typedef struct {
    float x, y, z;
} Vec3;

void init_vec3(Vec3 *v, float x, float y, float z);
void add_vec3(Vec3 *v1, const Vec3 *v2);
void sub_vec3(Vec3 *v1, const Vec3 *v2);
void normalize_vec3(Vec3 *v);

typedef enum {
    X = 0,
    Y = 1, 
    Z = 2
} Axis;

#endif // UTIL_H