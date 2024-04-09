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

        [[nodiscard]] int getW() const { return w; }
        [[nodiscard]] int getH() const { return h; }
        [[nodiscard]] int getC() const { return c; }
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

