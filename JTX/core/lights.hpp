#pragma once
#include "JTX/util/util.hpp"

namespace JTX::Core {
class DirLight {
public:
  explicit DirLight(JTX::Util::Vec3 direction, float lightIntensity) {
    if (lightIntensity < 0.0f || lightIntensity > 1.0f) {
      throw std::invalid_argument(
          "Intensity must be greater be in the range [0.0f, 1.0f]");
    }
    this->direction_ = direction.normalize();
    this->intensity_ = lightIntensity;
  }
  ~DirLight() = default;

  [[nodiscard]] const JTX::Util::Vec3 &getDirection() const {
    return direction_;
  }

  [[nodiscard]] float getIntensity(const JTX::Util::Vec3 &normal) const {
    return this->intensity_ * std::max(0.0f, -normal.dot(direction_));
  }

private:
  JTX::Util::Vec3 direction_;
  float intensity_;
};
} // namespace JTX::Core
