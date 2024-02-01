#include "model.h"

static const int INITIAL_CAPACITY = 100;

void init_model(Model *m, int num_v, int num_f) {
  m->v = (Vertex *)malloc(num_v * sizeof(Vertex));
  m->num_f = num_f;
  m->f = (Face *)malloc(num_f * sizeof(Face));
  m->num_v = num_v;
  m->n = (Vertex *)malloc(num_v * sizeof(Vertex));
}

void free_model(Model *m) {
  free(m->v);
  free(m->f);
  free(m->n);
}

void load_model(Model *m, const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char line[128];
  Vertex *v = malloc(INITIAL_CAPACITY * sizeof(Vertex));
  int num_v = 0;
  int v_capacity = INITIAL_CAPACITY;
  Face *f = malloc(INITIAL_CAPACITY * sizeof(Face));
  int num_f = 0;
  int f_capacity = INITIAL_CAPACITY;

  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "v ", 2) == 0) {
      if (num_v == v_capacity) {
        v_capacity *= 2;
        v = realloc(v, v_capacity * sizeof(Vertex));
      }
      Vertex vert;
      if (sscanf(line, "v %f %f %f", &vert.x, &vert.y, &vert.z) == 3) {
        vert.w = 1.0f;
        v[num_v++] = vert;
      }
    } else if (strncmp(line, "f ", 2) == 0) {
      if (num_f == f_capacity) {
        f_capacity *= 2;
        f = realloc(f, f_capacity * sizeof(Face));
      }
      Face face;
      if (sscanf(line, "f %d %d %d", &face.v1, &face.v1, &face.v1) == 3) {
        face.v1--;
        face.v2--;
        face.v3--;
        f[num_f++] = face;
      }
    }
  }

  fclose(file);
  v = realloc(v, num_v * sizeof(Vertex));
  f = realloc(f, num_f * sizeof(Face));

  m->v = v;
  m->num_v = num_v;
  m->f = f;
  m->num_f = num_f;
  m->n = malloc(num_v * sizeof(Vertex));
}