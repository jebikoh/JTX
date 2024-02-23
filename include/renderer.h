#ifndef RENDERER_H
#define RENDERER_H

#include "scene.h"
#include "camera.h"
#include <math.h>

typedef struct {
    int w, h;
    int ar;
    int mlen;
    Camera c;
    float *fb;
    float *zbuf;
} Renderer;

/**
 * @brief Initializes a new renderer
 * 
 * @param r Renderer
 * @param w Display width
 * @param h Display height
 * @param fb Pointer to framebuffer; if NULL is passed, internal frambuffer will be allocated
 * @param c Camera
 * 
 * @return 0 on success, -1 on memory allocation failure
 */
int renderer_init(Renderer *r, int w, int h, float **fb, Camera c);

/**
 * @brief Frees the memory allocated by the renderer.
 * 
 * @param r Renderer
 * @param free_fb If 1, framebuffer will be freed (caution with external framebuffers)
 */
void renderer_free(Renderer *r, int free_fb);

/**
 * @brief Clears frame- and z-buffers
 * 
 * @param r Renderer
 */
void renderer_clear(Renderer *r);

void renderer_set_camera(Renderer *r, Camera c);
void renderer_render_scene(Renderer *r, Scene *s);


#endif // RENDERER_H