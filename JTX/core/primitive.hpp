#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cblas.h>
#include "JTX/util/util.hpp"

namespace JTX::Core {

    struct Face {
        int v1, v2, v3;
        int vt1, vt2, vt3;
        int vn1, vn2, vn3;
    };

    class Primitive {
    public:
        Primitive();
        ~Primitive();

        void load(const std::string& path);

        void applyTransform(const JTX::Util::Mat4* tf);

        void calculateNormals();

        inline const float* getNormal(int i) const {
            return n_ + (3 * i);
        };

        inline float *getVertex(int i) {
            return v_ + 4 * i;
        }

        [[nodiscard]] inline const float *getVertexNormal(int i) const {
            return vn_ + 4 * i;
        }

        inline int *getScreen(int i) {
            return screen_ + 2 * i;
        }

        [[nodiscard]] inline Face *getFace(int i) const {
            return f_ + i;
        }

        inline float *getNormal(int i) {
            return n_ + 3 * i;
        }

        [[nodiscard]] inline int getNumVertices() const {
            return num_v_;
        };
        [[nodiscard]] inline int getNumFaces() const {
            return num_f_;
        };
    private:
        int num_v_, num_vt_, num_vn_, num_f_;
        float *v_;
        float *vt_;
        float *vn_;
        Face *f_;
        float *n_;
        int *screen_;
    };
} // JTX
