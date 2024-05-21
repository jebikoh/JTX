#pragma once

#include <cmath>
#include <stdexcept>

namespace JTX::Util {
/**
 * @class Vec3
 * @brief A simple 3D vector class
 *
 * This class is used to represent a 3D vector in the JTX engine.
 * It provides basic vector operations such as add/sub, dot/cross product, etc.
 * All methods are marked as inline for performance
 */
class Vec3 {
public:
  float x, y, z;

  /**
   * @brief Default constructor
   *
   * Initializes vector zero-vector
   */
  Vec3() : x(0), y(0), z(0){};
  /**
   * @brief XYZ constructor
   * @param x
   * @param y
   * @param z
   */
  Vec3(float x, float y, float z) : x(x), y(y), z(z){};
  ~Vec3() = default;

  inline bool operator==(const Vec3 &other) const {
    return (x == other.x) && (y == other.y) && (z == other.z);
  }
  inline bool operator!=(const Vec3 &other) const { return !(*this == other); }
  inline Vec3 operator+(const Vec3 &other) const {
    return {x + other.x, y + other.y, z + other.z};
  }
  inline Vec3 operator-(const Vec3 &other) const {
    return {x - other.x, y - other.y, z - other.z};
  }
  inline Vec3 operator*(const Vec3 &other) const {
    return {x * other.x, y * other.y, z * other.z};
  }
  inline Vec3 operator+=(const Vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  inline Vec3 operator-=(const Vec3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  [[nodiscard]] inline Vec3 cross(const Vec3 &other) const {
    return {y * other.z - z * other.y, z * other.x - x * other.z,
            x * other.y - y * other.x};
  }

  [[nodiscard]] inline float dot(const Vec3 &other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  [[nodiscard]] inline float dot(const float _x, const float _y,
                                 const float _z) const {
    return this->x * _x + this->y * _y + this->z * _z;
  }

  [[nodiscard]] inline float len() const {
    return std::sqrt(x * x + y * y + z * z);
  }

  /**
   * @brief Normalize vector (in-place)
   *
   * Normalizes the vector to a unit vector
   * @return Reference to this vector
   */
  inline Vec3 &normalize() {
    float l = len();
    if (l != 0) {
      x /= l;
      y /= l;
      z /= l;
    } else {
      throw std::runtime_error("Cannot normalize a zero vector");
    }
    return *this;
  }

  /**
   * @brief Normalize vector
   * @return Normalized vector as a new Vec3
   */
  [[nodiscard]] inline Vec3 normalized() const {
    float l = len();
    if (l != 0) {
      return Vec3{x / l, y / l, z / l};
    } else {
      throw std::runtime_error("Cannot normalize a zero vector");
    }
  }
};
} // namespace JTX::Util
