#pragma once

#include "constants.hpp"
#include <cmath>
#include <stdexcept>

namespace jtx {

    // Only allow numeric types
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    class Vec4 {
    public:
        T x, y, z, w;

        // Constructors
        Vec4() : x(JTX_ZERO), y(JTX_ZERO), z(JTX_ZERO), w(JTX_ZERO) {};
        Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
        Vec4(const Vec4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};
        ~Vec4() = default;

        // Unary operators
        inline Vec4 operator-() const {
            return {-x, -y, -z, -w};
        }
        inline Vec4 operator+() const {
            return {+x, +y, +z, +w};
        }
        inline Vec4& operator++() {
            x++;
            y++;
            z++;
            w++;
            return *this;
        }
        inline Vec4 operator++(int) {
            Vec4 temp = *this;
            x++;
            y++;
            z++;
            w++;
            return temp;
        }
        inline Vec4& operator--() {
            x--;
            y--;
            z--;
            w--;
            return *this;
        }
        inline Vec4 operator--(int) {
            Vec4 temp = *this;
            x--;
            y--;
            z--;
            w--;
            return temp;
        }

        // Binary operators
        inline Vec4& operator=(const Vec4& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
            return *this;
        }
        inline bool operator==(const Vec4& other) const {
            return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
        }
        inline bool operator!=(const Vec4& other) const {
            return (x != other.x) || (y != other.y) || (z != other.z) && (w != other.w);
        }
        inline Vec4 operator+(const Vec4& other) const {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }
        inline Vec4 operator-(const Vec4& other) const {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }
        inline Vec4 operator*(const Vec4& other) const {
            return {x * other.x, y * other.y, z * other.z, w * other.w};
        }
        inline Vec4 operator*(T scalar) const {
            return {x * scalar, y * scalar, z * scalar, w * scalar};
        }
        inline Vec4 operator/(const Vec4& other) const{
            return {x / other.x, y / other.y, z / other.z, w / other.w};
        }
        inline Vec4 operator/(T scalar) const {
            return {x / scalar, y / scalar, z / scalar, w / scalar};
        }

        // In-place Assignment Operators
        inline Vec4& operator+=(const Vec4& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }
        inline Vec4& operator-=(const Vec4& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }
        inline Vec4& operator*=(const Vec4& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }
        inline Vec4& operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }
        inline Vec4& operator/=(const Vec4& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return *this;
        }
        inline Vec4& operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }

        // Member functions
        [[nodiscard]] inline T dot(const Vec4 &other) const {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        [[nodiscard]] inline T dot(const T _x, const T _y, const T _z, const T _w) const {
            return this->x * _x + this->y * _y + this->z * _z + this->w * _w;
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y + z * z + w * w); }

        inline Vec4& normalize() {
            float l = len();
            if (l != 0) {
                x /= l;
                y /= l;
                z /= l;
                w /= l;
            }
            return *this;
        }

        [[nodiscard]] inline Vec4 normalized() const {
            float l = len();
            if (l != 0) {
                return {x / l, y / l, z / l, w / l};
            } else {
                return Vec4{};
            }
        }
    };

    typedef Vec4<int> Vec4i;
    typedef Vec4<float> Vec4f;

}// namespace jtx
