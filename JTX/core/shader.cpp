#include "shader.hpp"

namespace JTX::Core {
inline void DefaultShader::vertex(float *vertex) {
  JTX::Util::applyTransform(ub_->cameraMatrix, vertex);
}

void DefaultShader::fragment(const float *bary, const int *screen,
                             const float *normal, float *color) {
  return;
}
} // namespace JTX::Core