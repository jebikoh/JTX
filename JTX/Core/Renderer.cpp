#include "Renderer.h"

JTX::Core::Renderer::Renderer(int w, int h, int c) {
    if (w <= 0 || h <= 0 || c <= 0) {throw std::invalid_argument("Invalid dimensions");}

    this->w = w;
    this->h = h;
    this->c = c;
    this->ar = (float)w / (float)h;
    this->fb = new float[c * h * w]();
    this->zb = new float[h * w];

    for (int i = 0; i < w * h; i++) {this->zb[i] = 1.0f;}
}

void JTX::Core::Renderer::clear() {
    // TODO: optimize this later
    std::memset(fb, 0, c * h * w * sizeof(float));
    std::memset(zb, 1, h * w * sizeof(float));
}

void JTX::Core::Renderer::render(JTX::Core::Scene *scene) {
    // To-do
}

void JTX::Core::Renderer::drawLine(int x0, int y0, int x1, int y1, int ch, float val) {
    if (x0 < 0 || x0 >= this->w || y0 < 0 || y0 >= this->h || x1 < 0 || x1 >= this->w || y1 < 0 || y1 >= this->h) {
        throw std::invalid_argument("Line out of bounds");
    }

    if (x0 == x1) {
        if (y0 > y1) {std::swap(y0, y1);}
        for (int y = y0; y <= y1; ++y) {
            drawPixel(x0, y, ch, val);
        }
        return;
    }

    if (y0 == y1) {
        if (x0 > x1) {std::swap(x0, x1);}
        for (int x = x0; x <= x1; ++x) {
            drawPixel(x, y0, ch, val);
        }
        return;
    }

    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);
    int err = dx >> 1;
    int sy = (y0 < y1) ? 1 : -1;
    int y = y0;

    if (steep) {
        for (int x = x0; x <= x1; ++x) {
            drawPixel(y, x, ch, val);
            err -= dy;
            if (err < 0) {
                y += sy;
                err += dx;
            }
        }
    } else {
        for (int x = x0; x <= x1; ++x) {
            drawPixel(x, y, ch, val);
            err -= dy;
            if (err < 0) {
                y += sy;
                err += dx;
            }
        }
    }
}

