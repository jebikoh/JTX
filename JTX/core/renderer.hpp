#pragma once

#include <stdexcept>
#include <iostream>
#include "JTX/core/scene.hpp"
#include "JTX/util/util.hpp"
#include "external/fpng.h"

namespace JTX::Core {
    class Renderer {
    public:
        Renderer(int w, int h, int c=3);
        ~Renderer() {
            delete[] fb;
            delete[] zb;
        };

        void clear();

        inline void drawPixel(int x, int y, int channel, float val) {
            if (x < 0 || x >= this->w || y < 0 || y >= this->h || channel < 0 || channel >= this->c) {
                throw std::invalid_argument("Pixel out of bounds or invalid channel");
            }
            this->fb[channel * (this->h * this->w) + (y * this->w) + x] = val;
        }
        inline void drawPixel(int x, int y, float r, float g, float b) {
            if (x < 0 || x >= this->w || y < 0 || y >= this->h || this->c != 3) {
                throw std::invalid_argument("Pixel out of bounds or invalid channel");
            }
            this->fb[(y * this->w) + x] = r;
            this->fb[(this->h * this->w) + (y * this->w) + x] = g;
            this->fb[2 * (this->h * this->w) + (y * this->w) + x] = b;
        }
        inline float getPixel(int x, int y, int ch) {
            if (x < 0 || x >= this->w || y < 0 || y >= this->h || ch < 0 || ch >= this->c) {
                throw std::invalid_argument("Pixel out of bounds or invalid channel");
            }
            return this->fb[ch * (this->h * this->w) + (y * this->w) + x];
        }

        // Bresenhams Line
        void drawLine(int x0, int y0, int x1, int y1, float r, float g, float b);
        inline void drawLine(int x0, int y0, int x1, int y1, JTX::Util::Color color) {
            drawLine(x0, y0, x1, y1, color.r, color.g, color.b);
        }

        // Bounding-box
        void drawTriangle(int x0, int y0, float z0, int x1, int y1, float z1,  int x2, int y2, float z2, float r, float g, float b);
        inline void drawTriangle(int x0, int y0, float z0, int x1, int y1, float z1,  int x2, int y2, float z2, JTX::Util::Color color) {
            drawTriangle(x0, y0, z0, x1, y1, z1, x2, y2, z2, color.r, color.g, color.b);
        }

        void render(Scene* scene, ProjectionType projType=PERSPECTIVE);
        // THIS FUNCTION REQUIRES ALL VERTICES TO BE BETWEEN -1 AND 1
        void renderWireframe(JTX::Core::Primitive &p, JTX::Util::Color color);

        [[nodiscard]] int getWidth() const { return w; }
        [[nodiscard]] int getHeight() const { return h; }
        [[nodiscard]] int getChannels() const { return c; }
        [[nodiscard]] float getAR() const { return ar; }

        void saveFb(const std::string &path, int compressionLevel);

    private:
        int w, h, c;
        float ar;
        float *fb;
        float *zb;

        static inline int edgeFn(int x0, int y0, int x1, int y1, int tx, int ty) {
            // This is the signed area of a parallelogram
            return (tx - x0) * (y1 - y0) - (ty - y0) * (x1 - x0);
        }

        inline float getDepth(int x, int y) {
            if (x < 0 || x >= this->w || y < 0 || y >= this->h) {
                throw std::invalid_argument("Pixel out of bounds");
            }
            return this->zb[y * this->w + x];
        }

        inline void setDepth(int x, int y, float z) {
            if (x < 0 || x >= this->w || y < 0 || y >= this->h) {
                throw std::invalid_argument("Pixel out of bounds");
            }
            this->zb[y * this->w + x] = z;
        }
    };
}

