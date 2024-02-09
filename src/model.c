#include "model.h"

static const int INITIAL_CAPACITY = 100;

void model_init(Model *m, int num_v, int num_f) {
  m->v = (float *)malloc(4 * num_v * sizeof(float));
  m->num_f = num_f;
  m->f = (Face *)malloc(num_f * sizeof(Face));
  m->num_v = num_v;
  m->n = (float *)malloc(4 * num_v * sizeof(float));
}

void model_free(Model *m) {
  free(m->v);
  free(m->f);
  free(m->n);
}

void model_load(Model *m, const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char line[128];
  float *v = malloc(4 * INITIAL_CAPACITY * sizeof(float));
  int num_v = 0;
  int v_capacity = INITIAL_CAPACITY;
  Face *f = malloc(INITIAL_CAPACITY * sizeof(Face));
  int num_f = 0;
  int f_capacity = INITIAL_CAPACITY;

  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "v ", 2) == 0) {
      if (num_v == v_capacity) {
        v_capacity *= 2;
        v = realloc(v, 4 * v_capacity * sizeof(float));
      }
      float x, y, z;
      if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
        int i = 4 * num_v;
        v[i] = x;
        v[i + 1] = y;
        v[i + 2] = z;
        v[i + 3] = 1.0f;
        num_v++;
      }
    } else if (strncmp(line, "f ", 2) == 0) {
      if (num_f == f_capacity) {
        f_capacity *= 2;
        f = realloc(f, f_capacity * sizeof(Face));
      }
      Face face;
      if (sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &face.v1, &face.v2,
                 &face.v3) == 3) {
        face.v1--;
        face.v2--;
        face.v3--;
        f[num_f++] = face;
      }
    }
  }

  fclose(file);
  v = realloc(v, 4 * num_v * sizeof(float));
  f = realloc(f, num_f * sizeof(Face));

  m->v = v;
  m->num_v = num_v;
  m->f = f;
  m->num_f = num_f;
  m->n = malloc(4 * num_v * sizeof(float));
}

float *model_get_v(const Model *m, int i) { return m->v + 4 * i; }

void model_apply_transf(Model *m, const Mat4 *tf) {
  int size = 4 * m->num_v;
  float *new_v = malloc(size * sizeof(float));
  if (!new_v) {
    perror("Failed to allocate memory for transformed vertices");
    return;
  }

  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m->num_v, 4, 4, 1.0f,
              m->v, 4, (float *)tf->m, 4, 0.0f, new_v, 4);

  free(m->v);
  m->v = new_v;
}