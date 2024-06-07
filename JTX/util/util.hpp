#pragma once

#include "JTX/util/color.hpp"
#include "JTX/util/mat4.hpp"
#include "JTX/util/vec2.hpp"
#include "JTX/util/vec3.hpp"
#include "JTX/util/vec4.hpp"
#include <cmath>
#include <queue>

namespace JTX::Util {
static inline float degToRad(float deg) { return deg * (M_PI / 180.0f); }

/**
 * A simple ID pool that can be used to get and release IDs. Re-used IDs are
 * returned before new ones are given.
 *
 * Will be depracated soon
 */
class IDPool {
public:
  IDPool() : nextID_(0) {}
  ~IDPool() = default;

  [[nodiscard]] uint64_t getID() {
    if (pool_.empty()) {
      return nextID_++;
    }
    uint64_t id = pool_.front();
    pool_.pop();
    return id;
  }

  void releaseID(uint64_t id) { pool_.push(id); }

private:
  std::queue<uint64_t> pool_;
  uint64_t nextID_;
};

/**
 * Applies an affine transformation to a 4D vector in-place
 * @param tf 4x4 affine transformation (Mat4)
 * @param v 4D vector to transform. If the array is not of size 4, the behavior
 * is undefined
 *
 * NOTE: this method is not safe and does not check for the size of the array
 */
static void applyTransform(const Mat4 &tf, Util::Vec4f &v) {
  float x = v.x * tf[0][0] + v.y * tf[0][1] + v.z * tf[0][2] + v.w * tf[0][3];
  float y = v.x * tf[1][0] + v.y * tf[1][1] + v.z * tf[1][2] + v.w * tf[1][3];
  float z = v.x * tf[2][0] + v.y * tf[2][1] + v.z * tf[2][2] + v.w * tf[2][3];
  float w = v.x * tf[3][0] + v.y * tf[3][1] + v.z * tf[3][2] + v.w * tf[3][3];

  v.x = x;
  v.y = y;
  v.z = z;
  v.w = w;
}
} // namespace JTX::Util