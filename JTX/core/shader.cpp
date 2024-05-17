#include "shader.hpp"

namespace JTX::Core {
    void DefaultShader::vertex(const float *vertex, float *out) {
        JTX::Util::applyTransform(&ub_->cameraMatrix, vertex, out);
    }

    void DefaultShader::fragment(const float *bary, const int *screen, const float *normal, float *color) {

    }
}