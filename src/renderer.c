#include "renderer.h"

int renderer_init(Renderer *r, int w, int h, float **fb, Camera c) {
  r->zbuf = malloc(sizeof(float) * w * h);
  if (r->zbuf == NULL) {
    return -1;
  }
  if (fb == NULL) {
    r->fb = calloc(w * h, sizeof(float));
    if (r->fb == NULL) {
      free(r->zbuf);
      return -1;
    }
  } else {
    r->fb = *fb;
  }
  // Set zbuf to -inf
  // No need to use SIMD here
  for (int i = 0; i < w * h; i++) {
    r->zbuf[i] = -INFINITY;
  }

  r->w = w;
  r->h = h;
  r->ar = (float)w / (float)h;
  r->mlen = (int)sqrtf((float)(w * w + h * h));
  r->c = c;

  return 0;
}

void renderer_free(Renderer *r, int free_fb) {
  if (free_fb) {
    free(r->fb);
  }
  free(r->zbuf);
}

void renderer_clear(Renderer *r) {
  // Optimize this loop later
  // Needs to be called every frame
  for (int i = 0; i < r->w * r->h; i++) {
    r->zbuf[i] = -INFINITY;
    r->fb[i] = 0.0f;
  }
}