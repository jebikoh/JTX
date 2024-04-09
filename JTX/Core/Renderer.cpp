#include "Renderer.h"

JTX::Core::Renderer::Renderer(int w, int h, int c) {
    if (w <= 0 || h <= 0 || c <= 0) {throw std::invalid_argument("Invalid dimensions");}

    this->w = w;
    this->h = h;
    this->c = c;
    this->ar = (float)w / (float)h;
    this->fb = new float[w * h * c]();
    this->zb = new float[w * h];

    for (int i = 0; i < w * h; i++) {this->zb[i] = 1.0f;}
}

void JTX::Core::Renderer::clear() {
    for (int i = 0; i < w * h * c; i++) {
        fb[i] = 0.0f;
    }

    for (int i = 0; i < w * h; i++) {
        zb[i] = 1.0f;
    }
}

void JTX::Core::Renderer::render(JTX::Core::Scene *scene) {

}
