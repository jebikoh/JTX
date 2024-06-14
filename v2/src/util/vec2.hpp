#pragma once

#include<cmath>
#include<stdexcept>
#include "constants.hpp"

namespace jtx {
    // Only allow numeric types
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    class Vec2 {
    public:
        T x, y;

        // Constructors
        Vec2() : x(JTX_ZERO), y(JTX_ZERO) {};
        Vec2(T x, T y) : x(x), y(y) {};
        Vec2(const Vec2& other) : x(other.x), y(other.y) {};
        ~Vec2() = default;

        // Unary operators
        inline Vec2 operator-() const {
            return {-x, -y};
        }
        inline Vec2 operator+() const {
            return {+x, +y};
        }
        inline Vec2& operator++() {
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
        inline Vec2& operator--() {
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

        // Binary operators
        inline Vec2& operator=(const Vec2& other) {
            x = other.x;
            y = other.y;
            return *this;
        }
        inline bool operator==(const Vec2& other) const {
            return (x == other.x) && (y == other.y);
        }
        inline bool operator!=(const Vec2& other) const {
            return (x != other.x) || (y != other.y);
        }
        inline Vec2 operator+(const Vec2& other) const {
            return {x + other.x, y + other.y};
        }
        inline Vec2 operator-(const Vec2& other) const {
            return {x - other.x, y - other.y};
        }
        inline Vec2 operator*(const Vec2& other) const {
            return {x * other.x, y * other.y};
        }
        inline Vec2 operator*(T scalar) const {
            return {x * scalar, y * scalar};
        }
        inline Vec2 operator/(const Vec2& other) const{
            return {x / other.x, y / other.y};
        }
        inline Vec2 operator/(T scalar) const {
            return {x / scalar, y / scalar};
        }

        // In-place Assignment Operators
        inline Vec2& operator+=(const Vec2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        inline Vec2& operator-=(const Vec2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        inline Vec2& operator*=(const Vec2& other) {
            x *= other.x;
            y *= other.y;
            return *this;
        }
        inline Vec2& operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
        inline Vec2& operator/=(const Vec2& other) {
            x /= other.x;
            y /= other.y;
            return *this;
        }
        inline Vec2& operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        // Member functions
        [[nodiscard]] inline T dot(const Vec2 &other) const {
            return x * other.x + y * other.y;
        }

        [[nodiscard]] inline T dot(const T _x, const T _y) const {
            return this->x * _x + this->y * _y;
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y); }

        inline Vec2& normalize() {
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
    typedef Vec2<float> Vec2f;
}// namespace jtx
