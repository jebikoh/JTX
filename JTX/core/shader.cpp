#include "shader.hpp"

namespace JTX::Core {
    void DefaultShader::vertex(const float *vertex, const float *normal, float *out) {
        JTX::Util::Vec4 v(vertex[0], vertex[1], vertex[2], 1.0f);

    }

    void DefaultShader::fragment(const float *bary, const int *screen, const float *normal, float *color) {

    }
}