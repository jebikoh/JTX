#pragma once

#include <cmath>
#include <stdexcept>

namespace JTX::Util {
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Vec2 {
public:
  T x, y;

  Vec2() : x(0), y(0){};
  Vec2(T x, T y) : x(x), y(y){};
  ~Vec2() = default;

  inline bool operator==(const Vec2 &other) const {
    return (x == other.x) && (y == other.y);
  }
  inline bool operator!=(const Vec2 &other) const { return !(*this == other); }
  inline Vec2 operator+(const Vec2 &other) const {
    return {x + other.x, y + other.y};
  }
  inline Vec2 operator-(const Vec2 &other) const {
    return {x - other.x, y - other.y};
  }
  inline Vec2 operator*(const Vec2 &other) const {
    return {x * other.x, y * other.y};
  }
  inline Vec2 operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  inline Vec2 operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  [[nodiscard]] inline T dot(const Vec2 &other) const {
    return x * other.x + y * other.y;
  }

  [[nodiscard]] inline T dot(const T _x, const T _y) const {
    return this->x * _x + this->y * _y;
  }

  [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y); }

  inline Vec2 &normalize() {
    float l = len();
    if (l != 0) {
      x /= l;
      y /= l;
    }
    return *this;
  }

  [[nodiscard]] inline Vec2 normalized() const {
    float l = len();
    if (l != 0) {
      return {x / l, y / l};
    } else {
      return Vec2{};
    }
  }
};

typedef Vec2<int> Vec2i;
} // namespace JTX::Util
