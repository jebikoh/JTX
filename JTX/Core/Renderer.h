#pragma once

#include <stdexcept>
#include "JTX/Core/Scene.h"

namespace JTX::Core {
    class Renderer {
    public:
        Renderer(int w, int h, int c=1);
        ~Renderer() {
            delete[] fb;
            delete[] zb;
        };

        void clear();
        void render(Scene* scene);

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
        void drawLine(int x0, int y0, int x1, int y1, int ch, float val);

        [[nodiscard]] int getWidth() const { return w; }
        [[nodiscard]] int getHeight() const { return h; }
        [[nodiscard]] int getChannels() const { return c; }
        [[nodiscard]] float getAR() const { return ar; }
        float *getFB() { return fb; }
        float *getZB() { return zb; }

    private:
        int w, h, c;
        float ar;
        float *fb;
        float *zb;
    };
}

