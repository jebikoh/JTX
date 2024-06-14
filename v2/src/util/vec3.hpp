#pragma once

#include<cmath>
#include<stdexcept>
#include "./constants.hpp"
#include "./numerical.h"
#include "./assert.h"

namespace jtx {
    // Only allow numeric types
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    class Vec3 {
    public:
        T x, y, z;

        // Check for NaN
        inline bool valid() {
            return !(isNaN(x) || isNaN(y) || isNan(z));
        }

        // Constructors
        Vec3() : x(JTX_ZERO), y(JTX_ZERO), z(JTX_ZERO) {};

        Vec3(T x, T y, T z) : x(x), y(y), z(z) { ASSERT(valid()); };

        Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) { ASSERT(valid()); };

        ~Vec3() = default;

        // Unary operators
        inline Vec3 operator-() const {
            return {-x, -y, -z};
        }

        inline Vec3 operator+() const {
            return {+x, +y, +z};
        }

        inline Vec3 &operator++() {
            x++;
            y++;
            z++;
            return *this;
        }

        inline Vec3 operator++(int) {
            Vec3 temp = *this;
            x++;
            y++;
            z++;
            return temp;
        }

        inline Vec3 &operator--() {
            x--;
            y--;
            z--;
            return *this;
        }

        inline Vec3 operator--(int) {
            Vec3 temp = *this;
            x--;
            y--;
            z--;
            return temp;
        }

        // Binary operators
        inline Vec3 &operator=(const Vec3 &other) {
            ASSERT(other.valid());
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        inline bool operator==(const Vec3 &other) const {
            return (x == other.x) && (y == other.y) && (z == other.z);
        }

        inline bool operator!=(const Vec3 &other) const {
            return (x != other.x) || (y != other.y) || (z != other.z);
        }

        inline Vec3 operator+(const Vec3 &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        inline Vec3 operator-(const Vec3 &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        inline Vec3 operator*(const Vec3 &other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        inline Vec3 operator*(T scalar) const {
            return {x * scalar, y * scalar, z * scalar};
        }

        inline Vec3 operator/(const Vec3 &other) const {
            ASSERT(other.x != JTX_ZERO && other.y != JTX_ZERO && other.z != JTX_ZERO);
            return {x / other.x, y / other.y, z / other.z};
        }

        inline Vec3 operator/(T scalar) const {
            ASSERT(scalar != JTX_ZERO);
            return {x / scalar, y / scalar, z / scalar};
        }

        // In-place Assignment Operators
        inline Vec3 &operator+=(const Vec3 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            ASSERT(valid());
            return *this;
        }

        inline Vec3 &operator-=(const Vec3 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            ASSERT(valid());
            return *this;
        }

        inline Vec3 &operator*=(const Vec3 &other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            ASSERT(valid());
            return *this;
        }

        inline Vec3 &operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            ASSERT(valid());
            return *this;
        }

        inline Vec3 &operator/=(const Vec3 &other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            ASSERT(valid());
            return *this;
        }

        inline Vec3 &operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            ASSERT(valid());
            return *this;
        }

        // Member functions
        [[nodiscard]] inline Vec3 cross(const Vec3 &other) const {
            return {y * other.z - z * other.y, z * other.x - x * other.z,
                    x * other.y - y * other.x};
        }

        [[nodiscard]] inline T dot(const Vec3 &other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        [[nodiscard]] inline T dot(const T _x, const T _y, const T _z) const {
            return this->x * _x + this->y * _y + this->z * _z;
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y + z * z); }

        inline Vec3 &normalize() {
            float l = len();
            if (l != 0) {
                x /= l;
                y /= l;
                z /= l;
            }
            return *this;
        }

        static inline Vec3 normalize(const Vec3 &v) {
            float l = v.len();
            if (l != 0) {
                return {v.x / l, v.y / l, v.z / l};
            } else {
                return Vec3{};
            }
        }

        inline Vec3 &abs() {
            x = std::abs(x);
            y = std::abs(y);
            z = std::abs(z);
            return *this;
        }

        static inline Vec3 abs(const Vec3 &v) {
            return {std::abs(v.x), std::abs(v.y), std::abs(v.z)};
        }

        inline Vec3 &ceil() {
            x = jtx::ceil(x);
            y = jtx::ceil(y);
            z = jtx::ceil(z);
            return *this;
        }

        static inline Vec3 ceil(const Vec3 &v) {
            return {jtx::ceil(v.x), jtx::ceil(v.y), jtx::ceil(v.z)};
        }

        inline Vec3 &floor() {
            x = jtx::floor(x);
            y = jtx::floor(y);
            z = jtx::floor(z);
            return *this;
        }

        static inline Vec3 floor(const Vec3 &v) {
            return {jtx::floor(v.x), jtx::floor(v.y), jtx::floor(v.z)};
        }

        inline auto min() const {
            return std::min({x, y, z});
        }

        static inline Vec3 min(const Vec3 &a, const Vec3 &b) {
            return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
        }

        static inline Vec3 max(const Vec3 &a, const Vec3 &b) {
            return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
        }

        inline auto hprod() const {
            return x * y * z;
        }

        static inline auto hprod(const Vec3 &v) {
            return v.x * v.y * v.z;
        }

        static inline auto lerp(const Vec3 &a, const Vec3 &b, float t) {
            return (1 - t) * a + t * b;
        }

        static inline auto fma(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
            return a * b + c;
        }
    };


    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;
}// namespace jtx
