#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cblas.h>
#include "JTX/Util/Util.h"

namespace JTX::Core {

    struct Face {
        int v1, v2, v3;
    };

    class Primitive {
    public:
        Primitive();
        ~Primitive();

        void load(const std::string& path);

        void applyTransform(const JTX::Util::Mat4* tf);

        void calculateNormals();

        [[nodiscard]] const float* getNormal(int i) const;

        inline float *getVertex(int i) {
            return v + 4 * i;
        }

        inline int *getScreen(int i) {
            return screen + 2 * i;
        }

        inline Face *getFace(int i) {
            return f + i;
        }

        [[nodiscard]] int getNumVertices() const;
        [[nodiscard]] int getNumFaces() const;
    private:
        int num_v, num_f;
        float *v;
        Face *f;
        float *n;
        int *screen;
    };
} // JTX
