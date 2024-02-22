#ifndef SCENE_H
#define SCENE_H

#include "scene.h"
#include "primitive.h"
#include "lights.h"
#include "util.h"

typedef struct {
    Primitive **prims;
    int num_p;
    int cap_p;
    int *free_ids_p;
    int num_free_ids_p;
    DirLight *lights;
    int num_l;
    int cap_l;
    int *free_ids_l;
    int num_free_ids_l;
} Scene;

void scene_init(Scene *s, int cap_p, int cap_l);
void scene_free(Scene *s, int free_p);
int scene_add_prim(Scene *s, Primitive *p);
void scene_remove_prim(Scene *s, int id, int free_p);
int scene_add_light(Scene *s, DirLight l);
void scene_remove_light(Scene *s, int id);

#endif // SCENE_H