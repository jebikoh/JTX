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

void init_model(Model *m, int num_v, int num_f);
void free_model(Model *m);
void load_model(Model *m, const char *path);

#endif // MODEL_H