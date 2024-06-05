#pragma once
#include "JTX/util/util.hpp"

namespace JTX::Core {
struct UniformBuffer {
  JTX::Util::Mat4 cameraMatrix;
  JTX::Util::Vec3f lightDir;
  // Add as needed
};

class Shader {
public:
  virtual ~Shader() = default;

  inline virtual void vertex(float *vertex) = 0;
  virtual void fragment(const float *bary, const int *screen,
                        const float *normal, float *color) = 0;
  virtual void bind(const UniformBuffer &ub) = 0;
  virtual inline bool isBound() const = 0;
};

class DefaultShader : public Shader {
public:
  // TODO: passing the vertices as an array is pretty dangerous
  //       potential switch to passing Vec3f/Vec4f in the future
  inline void vertex(float *vertex) override;

  void fragment(const float *bary, const int *screen, const float *normal,
                float *color) override;

  void bind(const UniformBuffer &ub) override {
    this->ub_ = &ub;
    this->bound_ = true;
  }

  [[nodiscard]] inline bool isBound() const override { return bound_; }

private:
  const UniformBuffer *ub_;
  bool bound_ = false;
};
} // namespace JTX::Core
