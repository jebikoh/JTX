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

/**
 * @brief Initializes an empty model
 * 
 * @param m Pointer to output model
 * @param num_v Number of vertices
 * @param num_f Number of faces
 */
void model_init(Model *m, int num_v, int num_f);

/**
 * @brief Frees the memory allocated for a model
 * 
 * @param m Pointer to model
 */
void model_free(Model *m);

/**
 * @brief Loads a model from a .obj file. Model must be triangularized in advance
 * 
 * @param m Pointer to model
 * @param path Path to .obj file
 */
void model_load(Model *m, const char *path);

/**
 * @brief Get pointer to vertex. Vertices are a flat array of 4 floats: x, y, z, w
 * 
 * @param m Pointer to model
 * @param i Vertex number
 * @return float* Pointer to vertex. NULL if i is out of bounds
 */
float *model_get_v(const Model *m, int i);

/**
 * @brief Applies a transformation to vetices of a model in place.
 * 
 * @param m Pointer to model
 * @param tf Pointer to transformation
 */
void model_apply_transf(Model *m, const Mat4 *tf);

/**
 * @brief Computes the normal of a face.
 * 
 * @param m Pointer to model
 */
void model_comp_norms(Model *m);

#endif // MODEL_H