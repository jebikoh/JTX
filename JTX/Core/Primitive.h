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

        [[nodiscard]] const float* getVertex(int i) const;
        [[nodiscard]] int getNumVertices() const;
        [[nodiscard]] const Face* getFaces() const;
        [[nodiscard]] int getNumFaces() const;
    private:
        int num_v, num_f;
        float* v;
        Face* f;
        float* n;
    };
} // JTX
