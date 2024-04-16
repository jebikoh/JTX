#pragma once

#include <cmath>
#include <stdexcept>
#include <cblas.h>

namespace JTX::Util {
    class Vec3 {
    public:
        float x, y, z;

        Vec3() : x(0), y(0), z(0) {};
        Vec3(float x, float y, float z): x(x), y(y), z(z) {}
        ~Vec3() = default;

        inline bool operator==(const Vec3& other) const {
            return (x == other.x) && (y == other.y) && (z == other.z);
        }
        inline bool operator!=(const Vec3& other) const {
            return !(*this == other);
        }
        inline Vec3 operator+(const Vec3& other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        inline Vec3 operator+=(const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        inline Vec3 operator-(const Vec3& other) const {
            return {x - other.x, y - other.y, z - other.z};
        }
        inline Vec3 operator*(const Vec3& other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        [[nodiscard]] inline Vec3 cross(const Vec3& other) const {
            return {y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x};
        }

        [[nodiscard]] inline float dot(const Vec3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        [[nodiscard]] inline float dot(const float _x, const float _y, const float _z) const {
            return this->x * x + this->y * y + this->z * z;
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y + z * z); }

        inline Vec3& normalize() {
            float l = len();
            if (l != 0) { x /= l; y /= l; z /= l; }
            else { throw std::runtime_error("Cannot normalize a zero vector"); }
            return *this;
        }

        [[nodiscard]] inline Vec3 normalized() const {
            float l = len();
            if (l != 0) { return Vec3{ x / l, y / l, z / l}; }
            else { throw std::runtime_error("Cannot normalize a zero vector"); }
        }
    };
}
