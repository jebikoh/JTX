#pragma once

#include "./assert.hpp"
#include "./constants.hpp"
#include "./numerical.hpp"
#include <cmath>
#include <stdexcept>

namespace jtx {
    // Only allow numeric types
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    class Vec4 {
    public:
        T x, y, z, w;

        // Check for NaN
        [[nodiscard]] inline bool valid() const {
            return !(jtx::isNaN(x) || jtx::isNaN(y) || jtx::isNaN(z) || jtx::isNaN(w));
        }

        //region Constructors
        Vec4() : x(JTX_ZERO), y(JTX_ZERO), z(JTX_ZERO), w(JTX_ZERO) {};

        Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { ASSERT(valid()); };

        Vec4(const Vec4 &other) : x(other.x), y(other.y), z(other.z), w(other.w) { ASSERT(valid()); };

        template<typename U>
        explicit Vec4(const Vec4<U> &other) : x(T(other.x)), y(T(other.y)), z(T(other.z)), w(T(other.w)) {
            ASSERT(valid());
        };

        ~Vec4() = default;
        //endregion

        //region Unary operators
        inline Vec4 operator-() const {
            return {-x, -y, -z, -w};
        }

        inline Vec4 operator+() const {
            return {+x, +y, +z, +w};
        }

        inline Vec4 &operator++() {
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

        inline Vec4 &operator--() {
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
        //endregion

        //region Binary operators
        inline Vec4 &operator=(const Vec4 &other) {
            ASSERT(other.valid());
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
            return *this;
        }

        inline bool operator==(const Vec4 &other) const {
            return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
        }

        inline bool operator!=(const Vec4 &other) const {
            return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w);
        }

        inline Vec4 operator+(const Vec4 &other) const {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }

        inline Vec4 operator-(const Vec4 &other) const {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        inline Vec4 operator*(const Vec4 &other) const {
            return {x * other.x, y * other.y, z * other.z, w * other.w};
        }

        inline Vec4 operator*(T scalar) const {
            return {x * scalar, y * scalar, z * scalar, w * scalar};
        }

        friend inline Vec4 operator*(T scalar, const Vec4 &v) {
            return v * scalar;
        }

        inline Vec4 operator/(const Vec4 &other) const {
            ASSERT(JTX_ZERO != other.x && JTX_ZERO != other.y && JTX_ZERO != other.z && JTX_ZERO != other.w);
            return {x / other.x, y / other.y, z / other.z, w / other.w};
        }

        inline Vec4 operator/(T scalar) const {
            ASSERT(JTX_ZERO != scalar);
            return {x / scalar, y / scalar, z / scalar, w / scalar};
        }

        friend inline Vec4 operator/(T scalar, const Vec4 &v) {
            ASSERT(JTX_ZERO != scalar);
            return {scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w};
        }
        //endregion

        //region In-place Assignment Operators
        inline Vec4 &operator+=(const Vec4 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            ASSERT(valid());
            return *this;
        }

        inline Vec4 &operator-=(const Vec4 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            ASSERT(valid());
            return *this;
        }

        inline Vec4 &operator*=(const Vec4 &other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            ASSERT(valid());
            return *this;
        }

        inline Vec4 &operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            ASSERT(valid());
            return *this;
        }

        inline Vec4 &operator/=(const Vec4 &other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            ASSERT(valid());
            return *this;
        }

        inline Vec4 &operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            ASSERT(valid());
            return *this;
        }
        //endregion

        //region Member functions
        [[nodiscard]] inline T dot(const Vec4 &other) const {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        [[nodiscard]] inline T dot(const T _x, const T _y, const T _z, const T _w) const {
            return this->x * _x + this->y * _y + this->z * _z + this->w * _w;
        }

        inline Vec4 &abs() {
            x = std::abs(x);
            y = std::abs(y);
            z = std::abs(z);
            w = std::abs(w);
            return *this;
        }

        static inline Vec4 abs(const Vec4 &v) {
            return {std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)};
        }

        inline T absdot(const Vec4 &other) {
            return std::abs(dot(other));
        }

        static inline T absdot(const Vec4 &a, const Vec4 &b) {
            return std::abs(a.dot(b));
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y + z * z + w * w); }

        inline Vec4 &normalize() {
            float l = len();
            if (l != 0) {
                (*this) /= l;
            }
            return *this;
        }

        static inline Vec4 normalize(const Vec4 &v) {
            float l = v.len();
            if (l != 0) {
                return v / l;
            } else {
                return Vec4{};
            }
        }

        inline Vec4 &ceil() {
            x = jtx::ceil(x);
            y = jtx::ceil(y);
            z = jtx::ceil(z);
            w = jtx::ceil(w);
            return *this;
        }

        static inline Vec4 ceil(const Vec4 &v) {
            return {jtx::ceil(v.x), jtx::ceil(v.y), jtx::ceil(v.z), jtx::ceil(v.w)};
        }

        inline Vec4 &floor() {
            x = jtx::floor(x);
            y = jtx::floor(y);
            z = jtx::floor(z);
            w = jtx::floor(w);
            return *this;
        }

        static inline Vec4 floor(const Vec4 &v) {
            return {jtx::floor(v.x), jtx::floor(v.y), jtx::floor(v.z), jtx::floor(v.w)};
        }

        inline auto min() const {
            return std::min(std::min(z, w), std::min(x, y));
        }

        static inline Vec4 min(const Vec4 &a, const Vec4 &b) {
            return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)};
        }

        inline auto max() const {
            return std::max(std::max(z, w), std::max(x, y));
        }

        static inline Vec4 max(const Vec4 &a, const Vec4 &b) {
            return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)};
        }

        inline T hprod() const {
            return x * y * z * w;
        }

        static inline T hprod(const Vec4 &v) {
            return v.x * v.y * v.z * v.w;
        }

        static inline auto lerp(const Vec4 &a, const Vec4 &b, float t) {
            return a * (1 - t) + b * t;
        }

        static inline Vec4 fma(const Vec4 &a, const Vec4 &b, const Vec4 &c) {
            return a * b + c;
        }
        //endregion
    };


    typedef Vec4<int> Vec4i;
    typedef Vec4<float> Vec4f;
}// namespace jtx
