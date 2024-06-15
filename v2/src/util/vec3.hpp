#pragma once

#include<cmath>
#include<stdexcept>
#include "./constants.hpp"
#include "./numerical.hpp"
#include "./assert.hpp"
#include "./math.hpp"

namespace jtx {
    // Only allow numeric types
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    class Vec3 {
    public:
        T x, y, z;

        // Check for NaN
        [[nodiscard]] inline bool valid() const {
            return !(jtx::isNaN(x) || jtx::isNaN(y) || jtx::isNaN(z));
        }

        //region Constructors
        Vec3() : x(JTX_ZERO), y(JTX_ZERO), z(JTX_ZERO) {};

        Vec3(T x, T y, T z) : x(x), y(y), z(z) { ASSERT(valid()); };

        Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) { ASSERT(valid()); };

        ~Vec3() = default;
        //endregion

        //region Unary operators
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
        //endregion

        //region Binary operators
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

        friend inline Vec3 operator*(T scalar, const Vec3 &v) {
            return v * scalar;
        }

        inline Vec3 operator/(const Vec3 &other) const {
            ASSERT(JTX_ZERO != other.x && JTX_ZERO != other.y && JTX_ZERO != other.z);
            return {x / other.x, y / other.y, z / other.z};
        }

        inline Vec3 operator/(T scalar) const {
            ASSERT(JTX_ZERO != scalar);
            return {x / scalar, y / scalar, z / scalar};
        }

        friend inline Vec3 operator/(T scalar, const Vec3 &v) {
            ASSERT(JTX_ZERO != scalar);
            return {scalar / v.x, scalar / v.y, scalar / v.z};
        }
        //endregion

        //region In-place Assignment Operators
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
        //endregion

        //region Member functions
        static inline Vec3 cross(const Vec3 &a, const Vec3 &b) {
            return {jtx::dop(a.y, b.z, a.z, b.y),
                    jtx::dop(a.z, b.x, a.x, b.z),
                    jtx::dop(a.x, b.y, a.y, b.x)};
        }

        [[nodiscard]] inline T dot(const Vec3 &other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        [[nodiscard]] inline T dot(const T _x, const T _y, const T _z) const {
            return this->x * _x + this->y * _y + this->z * _z;
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

        inline T absdot(const Vec3 &other) {
            return std::abs(dot(other));
        }

        static inline T absdot(const Vec3 &a, const Vec3 &b) {
            return std::abs(a.dot(b));
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y + z * z); }

        inline Vec3 &normalize() {
            float l = len();
            if (l != 0) {
                (*this) /= l;
            }
            return *this;
        }

        static inline Vec3 normalize(const Vec3 &v) {
            float l = v.len();
            if (l != 0) {
                return v / l;
            } else {
                return Vec3{};
            }
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
            return std::min(z, std::min(x, y));
        }

        static inline Vec3 min(const Vec3 &a, const Vec3 &b) {
            return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
        }

        inline auto max() const {
            return std::max(z, std::max(x, y));
        }

        static inline Vec3 max(const Vec3 &a, const Vec3 &b) {
            return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
        }

        inline T hprod() const {
            return x * y * z;
        }

        static inline T hprod(const Vec3 &v) {
            return v.x * v.y * v.z;
        }

        static inline auto lerp(const Vec3 &a, const Vec3 &b, float t) {
            return a * (1 - t) + b * t;
        }

        static inline Vec3 fma(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
            return a * b + c;
        }

        static inline float angle(const Vec3 &a, const Vec3 &b) {
            if (a.dot(b) < 0) {
                return PI_F - 2 * std::asin((a - b).len() / 2);
            }
            return 2 * std::asin((a - b).len() / 2);
        }

        static inline Vec3 gramSchmidt(const Vec3 &a, const Vec3 &b) {
            return a - (b * a.dot(b));
        }
        //endregion
    };


    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;
}// namespace jtx
