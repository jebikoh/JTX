#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cblas.h>

typedef struct {
    int v1, v2, v3;
} Face;

typedef struct {
    float *v;
    int num_v;
    Face *f;
    int num_f;
    float *n;
} Primitive;


void prim_init(Primitive *m, int num_v, int num_f);
void prim_free(Primitive *m);
void prim_load(Primitive *m, const char *path);
void prim_apply_transf(Primitive *m, const Mat4 *tf);
void prim_comp_norms(Primitive *m);

/**
 * @brief Get pointer to vertex. Vertices are a flat array of 4 floats: x, y, z, w
 * 
 * @param m Pointer to primitive
 * @param i Vertex number
 * @return float* Pointer to vertex. NULL if i is out of bounds
 */
float *prim_get_v(const Primitive *m, int i);

#endif // PRIMITIVE_H