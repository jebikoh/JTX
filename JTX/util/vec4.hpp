#pragma once

#include "cblas.h"
#include <cmath>
#include <stdexcept>
// #include "mat4.hpp"

namespace JTX::Util {
/**
 * @class Vec4
 * @brief A simple 4D vector class
 *
 * This class is used to represent a 3D vector with a homogenous coordinate
 * It provides basic vector operations such as add/sub, dot product, etc. (no
 * cross). All methods are marked as inline for performance
 */
class Vec4 {
public:
  float x, y, z, w;

  /**
   * @brief Default constructor
   *
   * Initializes vector zero-vector
   */
  Vec4() : x(0), y(0), z(0), w(0){};
  /**
   * @brief XYZW constructor
   * @param x
   * @param y
   * @param z
   * @param w
   */
  Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};
  ~Vec4() = default;

  inline bool operator==(const Vec4 &other) const {
    return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
  }
  inline bool operator!=(const Vec4 &other) const { return !(*this == other); }
  inline Vec4 operator+(const Vec4 &other) const {
    return {x + other.x, y + other.y, z + other.z, w + other.w};
  }
  inline Vec4 operator-(const Vec4 &other) const {
    return {x - other.x, y - other.y, z - other.z, w - other.w};
  }
  inline Vec4 operator*(const Vec4 &other) const {
    return {x * other.x, y * other.y, z * other.z, w * other.w};
  }
  inline Vec4 operator+=(const Vec4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }
  inline Vec4 operator-=(const Vec4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }
  inline Vec4 operator*=(const Vec4 &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
  }

  inline float dot(const Vec4 &other) {
    return x * other.x + y * other.y + z * other.z + w * other.w;
  }
  inline float dot(const float _x, const float _y, const float _z,
                   const float _w) {
    return this->x * _x + this->y * _y + this->z * _z + this->w * _w;
  }
  [[nodiscard]] inline float len() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
  }

  /**
   * @brief Normalize vector (in-place)
   *
   * Normalizes the vector to a unit vector
   * @return Reference to this vector
   */
  inline Vec4 &normalize() {
    float l = len();
    if (l != 0) {
      x /= l;
      y /= l;
      z /= l;
      w /= l;
    } else
      throw std::runtime_error(
          "Vec4::normalize(): cannot normalize a zero vector");
    return *this;
  }

  /**
   * @brief Normalize vector
   *
   * Normalizes the vector to a unit vector
   * @return Normalized vector
   */
  [[nodiscard]] inline Vec4 normalized() const {
    float l = len();
    if (l != 0) {
      return {x / l, y / l, z / l, w / l};
    } else
      return Vec4{};
  }
};
} // namespace JTX::Util
