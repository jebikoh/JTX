#include "scene.h"

void scene_init(Scene *s, int cap_p, int cap_l) {
  if (cap_p < 1 || cap_l < 1) {
    fprintf(stderr,
            "Error: primitive and light capacity must be greater than 0\n");
    exit(1);
  }

  // Primitives
  s->prims = calloc(cap_p, sizeof(Primitive *));
  if (s->prims == NULL) {
    fprintf(stderr, "Error: calloc failed\n");
    exit(1);
  }
  s->num_p = 0;
  s->cap_p = cap_p;
  s->free_ids_p = malloc(cap_p * sizeof(int));
  if (s->free_ids_p == NULL) {
    fprintf(stderr, "Error: malloc failed\n");
    exit(1);
  }
  for (int i = 0; i < cap_p; i++) {
    s->free_ids_p[i] = i;
  }
  s->num_free_ids_p = cap_p;

  // Lights
  s->lights = malloc(cap_l * sizeof(DirLight));
  if (s->lights == NULL) {
    fprintf(stderr, "Error: malloc failed\n");
    exit(1);
  }
  s->num_l = 0;
  s->cap_l = cap_l;
  s->free_ids_l = malloc(cap_l * sizeof(int));
  if (s->free_ids_l == NULL) {
    fprintf(stderr, "Error: malloc failed\n");
    exit(1);
  }
  for (int i = 0; i < cap_l; i++) {
    s->free_ids_l[i] = i;
  }
  s->num_free_ids_l = cap_l;
}

void scene_free(Scene *s, int free_p) {
  if (free_p) {
    for (int i = 0; i < s->num_p; i++) {
      if (s->prims[i] != NULL) {
        prim_free(s->prims[i]);
      }
    }
  }

  free(s->prims);
  free(s->free_ids_p);
  free(s->lights);
  free(s->free_ids_l);
}

int scene_add_prim(Scene *s, Primitive *p) {
  if (s->num_free_ids_p == 0) {
    s->cap_p *= 2;

    s->prims = realloc(s->prims, s->cap_p * sizeof(Primitive *));
    if (s->prims == NULL) {
      fprintf(stderr, "Error: realloc failed\n");
      exit(1);
    }
    s->free_ids_p = realloc(s->free_ids_p, s->cap_p * sizeof(int));
    if (s->free_ids_p == NULL) {
      fprintf(stderr, "Error: realloc failed\n");
      exit(1);
    }

    for (int i = s->cap_p / 2; i < s->cap_p; i++) {
      s->free_ids_p[i] = i;
    }
    s->num_free_ids_p = s->cap_p / 2;
  }

  int id = s->free_ids_p[s->num_free_ids_p - 1];
  s->prims[id] = p;
  s->num_p++;
  s->num_free_ids_p--;

  return id;
}

void scene_remove_prim(Scene *s, int id, int free_p) {
  if (id < 0 || id >= s->cap_p) {
    fprintf(stderr, "Error: invalid id\n");
    exit(1);
  }
  if (free_p) {
    prim_free(s->prims[id]);
    s->prims[id] = NULL;
  }

  s->free_ids_p[s->num_free_ids_p] = id;
  s->num_free_ids_p++;
  s->num_p--;
}

int scene_add_light(Scene *s, DirLight l) {
  if (s->num_free_ids_l == 0) {
    s->cap_l *= 2;

    s->lights = realloc(s->lights, s->cap_l * sizeof(DirLight));
    if (s->lights == NULL) {
      fprintf(stderr, "Error: realloc failed\n");
      exit(1);
    }
    s->free_ids_l = realloc(s->free_ids_l, s->cap_l * sizeof(int));
    if (s->free_ids_l == NULL) {
      fprintf(stderr, "Error: realloc failed\n");
      exit(1);
    }

    for (int i = s->cap_l / 2; i < s->cap_l; i++) {
      s->free_ids_l[i] = i;
    }
    s->num_free_ids_l = s->cap_l / 2;
  }

  int id = s->free_ids_l[s->num_free_ids_l - 1];
  s->lights[id] = l;
  s->num_l++;
  s->num_free_ids_l--;

  return id;
}

void scene_remove_light(Scene *s, int id) {
  if (id < 0 || id >= s->cap_l) {
    fprintf(stderr, "Error: invalid id\n");
    exit(1);
  }

  s->free_ids_l[s->num_free_ids_l] = id;
  s->num_free_ids_l++;
  s->num_l--;
}