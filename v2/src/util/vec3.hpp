#pragma once

#include<cmath>
#include<stdexcept>
#include "./constants.hpp"
#include "./numerical.hpp"
#include "./assert.hpp"
#include "./math.hpp"

namespace jtx {
    JTX_NUM_ONLY
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

        template<typename U>
        explicit Vec3(const Vec3<U> &other) : x(T(other.x)), y(T(other.y)), z(T(other.z)) { ASSERT(valid()); };

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

        inline T absdot(const Vec3 &other) {
            return std::abs(dot(other));
        }

        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y + z * z); }

        inline Vec3 &normalize() {
            float l = len();
            if (l != 0) {
                (*this) /= l;
            }
            return *this;
        }

        inline Vec3 &ceil() {
            x = jtx::ceil(x);
            y = jtx::ceil(y);
            z = jtx::ceil(z);
            return *this;
        }

        inline Vec3 &floor() {
            x = jtx::floor(x);
            y = jtx::floor(y);
            z = jtx::floor(z);
            return *this;
        }

        inline auto min() const {
            return std::min(z, std::min(x, y));
        }

        inline auto max() const {
            return std::max(z, std::max(x, y));
        }

        inline T hprod() const {
            return x * y * z;
        }

        inline Vec3 &align(const Vec3 &other) {
            if ((*this).dot(other) < 0.0f) {
                (*this) = -(*this);
            }
            return *this;
        }
        //endregion
    };

    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;

    JTX_NUM_ONLY
    using Point3 = Vec3<T>;

    typedef Point3<int> Point3i;
    typedef Point3<float> Point3f;

    typedef Vec3<float> Normal3f;
}// namespace jtx
