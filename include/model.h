#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float x, y, z, w;
} Vertex;

typedef struct {
    int v1, v2, v3;
} Face;

typedef struct {
    Vertex *v;
    int num_v;
    Face *f;
    int num_f;
    Vertex *n;
} Model;

void model_init(Model *m, int num_v, int num_f);
void model_free(Model *m);
void model_load(Model *m, const char *path);
void model_apply_transf(Model *m, const Mat4 *tf);
void model_comp_norms(Model *m);

#endif // MODEL_H