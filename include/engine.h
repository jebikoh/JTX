#ifndef ENGINE_H
#define ENGINE_H

#include <math.h>

#include "camera.h"
#include "lights.h"
#include "model.h"
#include "util.h"

typedef struct {
  int w, h;           // buffer dimensions
  float ar;           // aspect ratio
  int mlen;           // minimum edge length
  int m_cap;          // model capacity
  int c_cap;          // camera capacity
  int dl_cap;         // dirlight capacity
  int num_c;          // number of cameras
  int num_m;          // number of models
  int num_dl;         // number of dirlights
  Model **models;     // models
  DirLight *dlights;  // dirlights
  Camera *cameras;    // cameras
  float *buf;         // framebuffer
  float *zbuf;        // z-buffer
} Engine;

void engine_init(Engine *e, int w, int h, int m_cap, int dl_cap, int c_cap);
int engine_add_model(Engine *e, Model *m);
int engine_add_dlight(Engine *e, DirLight l);
int engine_add_camera(Engine *e, Camera c);
void engine_remove_model(Engine *e, int id, int free_m);
void engine_remove_dlight(Engine *e, int id);
void engine_remove_camera(Engine *e, int id);
void engine_free(Engine *e, int free_m);

#endif  // ENGINE_H