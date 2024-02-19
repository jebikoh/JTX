#include "engine.h"

void engine_init(Engine *e, int w, int h, int m_cap, int dl_cap, int c_cap) {
  e->w = w;
  e->h = h;
  e->ar = (float)w / (float)h;
  e->mlen = (int)(sqrtf(e->w * e->w + e->h * e->h));
  e->m_cap = m_cap;
  e->num_m = 0;
  e->models = malloc(sizeof(Model *) * m_cap);
  if (!e->models) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  e->dl_cap = dl_cap;
  e->num_dl = 0;
  e->dlights = malloc(sizeof(DirLight) * dl_cap);
  if (!e->dlights) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  e->c_cap = c_cap;
  e->num_c = 0;
  e->cameras = malloc(sizeof(Camera) * c_cap);
  if (!e->cameras) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  e->buf = calloc(w * h, sizeof(float));
  if (!e->buf) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  e->zbuf = calloc(w * h, sizeof(float));
  if (!e->zbuf) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
}

void engine_free(Engine *e, int free_m) {
  if (free_m) {
    for (int i = 0; i < e->num_m; ++i) {
      model_free(e->models[i]);
    }
  }

  free(e->models);
  free(e->dlights);
  free(e->cameras);
  free(e->buf);
  free(e->zbuf);
}