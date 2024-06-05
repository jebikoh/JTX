#pragma once
#include "JTX/util/util.hpp"

namespace JTX::Core {
/**
 * @brief A directional light source
 * TODO: expand to other types of lights.
 * TOOD: add base class
 */
class DirLight {
public:
  /**
   * @brief Construct a new directional light object
   * @param direction Light direction
   * @param intensity Light intensity
   */
  explicit DirLight(JTX::Util::Vec3f direction, float intensity) {
    if (intensity < 0.0f || intensity > 1.0f) {
      throw std::invalid_argument(
          "Intensity must be greater be in the range [0.0f, 1.0f]");
    }
    this->direction_ = direction.normalize();
    this->intensity_ = intensity;
  }
  ~DirLight() = default;

  [[nodiscard]] const JTX::Util::Vec3f &getDirection() const {
    return direction_;
  }

  /**
   * Calculate the intensity of the light at a given point given surface normal
   * @param normal Surface normal
   * @return float Intensity of the light at the point
   */
  [[nodiscard]] float getIntensity(const JTX::Util::Vec3f &normal) const {
    return this->intensity_ * std::max(0.0f, -normal.dot(direction_));
  }

private:
  JTX::Util::Vec3f direction_;
  float intensity_;
};
} // namespace JTX::Core
