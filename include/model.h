#ifndef MODEL_H
#define MODEL_H

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
} Model;

void model_init(Model *m, int num_v, int num_f);
void model_free(Model *m);
void model_load(Model *m, const char *path);
float *model_get_v(const Model *m, int i);
void model_apply_transf(Model *m, const Mat4 *tf);
void model_comp_norms(Model *m);

#endif // MODEL_H