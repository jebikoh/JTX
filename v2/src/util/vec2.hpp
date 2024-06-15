#pragma once

#include<cmath>
#include<stdexcept>
#include "./constants.hpp"
#include "./numerical.hpp"
#include "./assert.hpp"

namespace jtx {
    // Only allow numeric types
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    class Vec2 {
    public:
        T x, y;

        // Check for NaN
        [[nodiscard]] inline bool valid() const {
            return !(jtx::isNaN(x) || jtx::isNaN(y));
        }

        //region Constructors
        Vec2() : x(JTX_ZERO), y(JTX_ZERO) {};

        Vec2(T x, T y) : x(x), y(y) { ASSERT(valid()); };

        Vec2(const Vec2 &other) : x(other.x), y(other.y) { ASSERT(valid()); };

        ~Vec2() = default;
        //endregion

        //region Unary operators
        inline Vec2 operator-() const {
            return {-x, -y};
        }

        inline Vec2 operator+() const {
            return {+x, +y};
        }

        inline Vec2 &operator++() {
            x++;
            y++;
            return *this;
        }

        inline Vec2 operator++(int) {
            Vec2 temp = *this;
            x++;
            y++;
            return temp;
        }

        inline Vec2 &operator--() {
            x--;
            y--;
            return *this;
        }

        inline Vec2 operator--(int) {
            Vec2 temp = *this;
            x--;
            y--;
            return temp;
        }
        //endregion

        //region Binary operators
        inline Vec2 &operator=(const Vec2 &other) {
            ASSERT(other.valid());
            x = other.x;
            y = other.y;
            return *this;
        }

        inline bool operator==(const Vec2 &other) const {
            return (x == other.x) && (y == other.y);
        }

        inline bool operator!=(const Vec2 &other) const {
            return (x != other.x) || (y != other.y);
        }

        inline Vec2 operator+(const Vec2 &other) const {
            return {x + other.x, y + other.y};
        }

        inline Vec2 operator-(const Vec2 &other) const {
            return {x - other.x, y - other.y};
        }

        inline Vec2 operator*(const Vec2 &other) const {
            return {x * other.x, y * other.y};
        }

        inline Vec2 operator*(T scalar) const {
            return {x * scalar, y * scalar};
        }

        friend inline Vec2 operator*(T scalar, const Vec2 &v) {
            return v * scalar;
        }

        inline Vec2 operator/(const Vec2 &other) const {
            ASSERT(JTX_ZERO != other.x && JTX_ZERO != other.y);
            return {x / other.x, y / other.y};
        }

        inline Vec2 operator/(T scalar) const {
            ASSERT(JTX_ZERO != scalar);
            return {x / scalar, y / scalar};
        }

        friend inline Vec2 operator/(T scalar, const Vec2 &v) {
            ASSERT(JTX_ZERO != v.x && JTX_ZERO != v.y);
            return {scalar / v.x, scalar / v.y};
        }
        //endregion

        //region In-place Assignment Operators
        inline Vec2 &operator+=(const Vec2 &other) {
            x += other.x;
            y += other.y;
            ASSERT(valid());
            return *this;
        }

        inline Vec2 &operator-=(const Vec2 &other) {
            x -= other.x;
            y -= other.y;
            ASSERT(valid());
            return *this;
        }

        inline Vec2 &operator*=(const Vec2 &other) {
            x *= other.x;
            y *= other.y;
            ASSERT(valid());
            return *this;
        }

        inline Vec2 &operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            ASSERT(valid());
            return *this;
        }

        inline Vec2 &operator/=(const Vec2 &other) {
            x /= other.x;
            y /= other.y;
            ASSERT(valid());
            return *this;
        }

        inline Vec2 &operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            ASSERT(valid());
            return *this;
        }
        //endregion

        //region Member functions
        [[nodiscard]] inline T dot(const Vec2 &other) const {
            return x * other.x + y * other.y;
        }

        [[nodiscard]] inline T dot(const T _x, const T _y) const {
            return this->x * _x + this->y * _y;
        }

        inline Vec2 &abs() {
            x = std::abs(x);
            y = std::abs(y);
            return *this;
        }

        static inline Vec2 abs(const Vec2 &v) {
            return {std::abs(v.x), std::abs(v.y)};
        }

        inline T absdot(const Vec2 &other) {
            return std::abs(dot(other));
        }

        static inline T absdot(const Vec2 &a, const Vec2 &b) {
            return std::abs(a.dot(b));
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y); }

        inline Vec2 &normalize() {
            float l = len();
            if (l != 0) {
                *this /= l;
            }
            return *this;
        }

        static inline Vec2 normalize(const Vec2 &v) {
            float l = v.len();
            if (l != 0) {
                return v / l;
            } else {
                return Vec2{};
            }
        }

        inline Vec2 &ceil() {
            x = jtx::ceil(x);
            y = jtx::ceil(y);
            return *this;
        }

        static inline Vec2 ceil(const Vec2 &v) {
            return {jtx::ceil(v.x), jtx::ceil(v.y)};
        }

        inline Vec2 &floor() {
            x = jtx::floor(x);
            y = jtx::floor(y);
            return *this;
        }

        static inline Vec2 floor(const Vec2 &v) {
            return {jtx::floor(v.x), jtx::floor(v.y)};
        }

        inline auto min() const {
            return std::min(x, y);
        }

        static inline Vec2 min(const Vec2 &a, const Vec2 &b) {
            return {std::min(a.x, b.x), std::min(a.y, b.y)};
        }

        inline auto max() const {
            return std::max(x, y);
        }

        static inline Vec2 max(const Vec2 &a, const Vec2 &b) {
            return {std::max(a.x, b.x), std::max(a.y, b.y)};
        }

        inline T hprod() const {
            return x * y;
        }

        static inline T hprod(const Vec2 &v) {
            return v.x * v.y;
        }

        static inline auto lerp(const Vec2 &a, const Vec2 &b, float t) {
            return a * (1 - t) + b * t;
        }

        static inline Vec2 fma(const Vec2 &a, const Vec2 &b, const Vec2 &c) {
            return a * b + c;
        }

        static inline float angle(const Vec2 &a, const Vec2 &b) {
            if (a.dot(b) < 0) {
                return PI_F - 2 * std::asin((a - b).len() / 2);
            }
            return 2 * std::asin((a - b).len() / 2);
        }

        static inline Vec2 gramSchmidt(const Vec2 &a, const Vec2 &b) {
            return a - (b * a.dot(b));
        }
        //endregion
    };


    typedef Vec2<int> Vec2i;
    typedef Vec2<float> Vec2f;
}// namespace jtx
