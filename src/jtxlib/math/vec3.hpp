#pragma once

#include <cmath>
#include <jtxlib/math/constants.hpp>
#include <jtxlib/math/math.hpp>
#include <jtxlib/math/numerical.hpp>
#include <jtxlib/util/assert.hpp>
#include <jtxlib/util/rand.hpp>
#include <jtxlib.hpp>
#include <stdexcept>

namespace jtx {
    template<typename T> class Vec2;
    template<typename T> class Vec4;

    //region Vec3
    template<typename T>
    class Vec3 {
        static_assert(std::is_arithmetic_v<T>, "Vec3 can only be instantiated with arithmetic types");
    public:
        union {
            struct {
                T x, y, z;
            };
            struct {
                T r, g, b;
            };
        };

        // Check for NaN
        [[nodiscard]] JTX_HOST JTX_INLINE bool valid() const {
            return !(jtx::isNaN(x) || jtx::isNaN(y) || jtx::isNaN(z));
        }

        //region Constructors
        JTX_HOSTDEV Vec3() : x(JTX_ZERO), y(JTX_ZERO), z(JTX_ZERO) {};

        JTX_HOSTDEV Vec3(T x, T y, T z) : x(x), y(y), z(z) {};

        JTX_HOSTDEV Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {};

        template<typename U>
        JTX_HOSTDEV explicit Vec3(const Vec3<U> &other) : x(T(other.x)), y(T(other.y)), z(T(other.z)) {};

        JTX_HOSTDEV Vec3(const Vec2<T> &other, T z) : x(other.x), y(other.y), z(z) {};
        JTX_HOSTDEV explicit Vec3(const Vec4<T> &other) : x(other.x), y(other.y), z(other.z) {};

        JTX_HOSTDEV ~Vec3() = default;
        //endregion

        //region Unary operators
        JTX_HOSTDEV JTX_INLINE Vec3 operator-() const {
            return {-x, -y, -z};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator+() const {
            return {+x, +y, +z};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator++() {
            x++;
            y++;
            z++;
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator++(int) {
            Vec3 temp = *this;
            x++;
            y++;
            z++;
            return temp;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator--() {
            x--;
            y--;
            z--;
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator--(int) {
            Vec3 temp = *this;
            x--;
            y--;
            z--;
            return temp;
        }
        //endregion

        //region Binary operators
        JTX_HOSTDEV JTX_INLINE Vec3 &operator=(const Vec3 &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE bool operator==(const Vec3 &other) const {
            return (x == other.x) && (y == other.y) && (z == other.z);
        }

        JTX_HOSTDEV JTX_INLINE bool operator!=(const Vec3 &other) const {
            return (x != other.x) || (y != other.y) || (z != other.z);
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator+(const Vec3 &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator+(const T scalar) const {
            return {x + scalar, y + scalar, z + scalar};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator-(const Vec3 &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator-(const T scalar) const {
            return {x - scalar, y - scalar, z - scalar};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator*(const Vec3 &other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator*(T scalar) const {
            return {x * scalar, y * scalar, z * scalar};
        }

        JTX_HOSTDEV friend JTX_INLINE Vec3 operator*(T scalar, const Vec3 &v) {
            return v * scalar;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator/(const Vec3 &other) const {
            ASSERT(JTX_ZERO != other.x && JTX_ZERO != other.y && JTX_ZERO != other.z);
            return {x / other.x, y / other.y, z / other.z};
        }

        JTX_HOSTDEV JTX_INLINE Vec3 operator/(T scalar) const {
            ASSERT(JTX_ZERO != scalar);
            return {x / scalar, y / scalar, z / scalar};
        }

        JTX_HOSTDEV friend JTX_INLINE Vec3 operator/(T scalar, const Vec3 &v) {
            ASSERT(JTX_ZERO != scalar);
            return {scalar / v.x, scalar / v.y, scalar / v.z};
        }
        //endregion

        //region In-place Assignment Operators
        JTX_HOSTDEV JTX_INLINE Vec3 &operator+=(const Vec3 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator+=(const T scalar) {
            x += scalar;
            y += scalar;
            z += scalar;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator-=(const Vec3 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator-=(const T scalar) {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator*=(const Vec3 &other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator/=(const Vec3 &other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            ASSERT(valid());
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE const T &operator[](int index) const {
            ASSERT(index >= 0 && index < 3);
            return (&x)[index];
        }

        JTX_HOSTDEV JTX_INLINE T &operator[](int index) {
            ASSERT(index >= 0 && index < 3);
            return (&x)[index];
        }
        //endregion

        //region Member functions
        JTX_HOSTDEV bool equals(const Vec3 &other, float epsilon = EPSILON) {
            return jtx::equals(x, other.x, epsilon) && jtx::equals(y, other.y, epsilon) &&
                   jtx::equals(z, other.z, epsilon);
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE T dot(const Vec3 &other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE T dot(const T _x, const T _y, const T _z) const {
            return this->x * _x + this->y * _y + this->z * _z;
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE Vec3 cross(const Vec3 &other) const {
            return {jtx::dop(y, other.z, z, other.y),
                    jtx::dop(z, other.x, x, other.z),
                    jtx::dop(x, other.y, y, other.x)};
        }


        JTX_HOSTDEV JTX_INLINE Vec3 &abs() {
            x = jtx::abs(x);
            y = jtx::abs(y);
            z = jtx::abs(z);
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE T absdot(const Vec3 &other) {
            return jtx::abs(dot(other));
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE float lenSqr() const {
            return x * x + y * y + z * z;
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE float len() const { return jtx::sqrt(lenSqr()); }

        JTX_HOSTDEV JTX_INLINE Vec3 &normalize() {
            float l = len();
            if (l != 0) {
                (*this) /= l;
            }
            return *this;
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE T l1norm() const {
            return jtx::abs(x) + jtx::abs(y) + jtx::abs(z);
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &ceil() {
            x = jtx::ceil(x);
            y = jtx::ceil(y);
            z = jtx::ceil(z);
            return *this;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &floor() {
            x = jtx::floor(x);
            y = jtx::floor(y);
            z = jtx::floor(z);
            return *this;
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE auto min() const {
            return jtx::min(z, jtx::min(x, y));
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE auto max() const {
            return jtx::max(z, jtx::max(x, y));
        }

        [[nodiscard]] JTX_HOSTDEV JTX_INLINE T hprod() const {
            return x * y * z;
        }

        JTX_HOSTDEV JTX_INLINE Vec3 &align(const Vec3 &other) {
            if ((*this).dot(other) < 0.0f) {
                (*this) = -(*this);
            }
            return *this;
        }
        //endregion
        //region Random
        JTX_HOST JTX_INLINE Vec3 random() {
            return {jtx::random<T>(), jtx::random<T>(), jtx::random<T>()};
        }

        JTX_HOST JTX_INLINE Vec3 random(T min, T max) {
            return {jtx::random<T>(min, max), jtx::random<T>(min, max), jtx::random<T>(min, max)};
        }
        //endregion
    };

    //region Type aliases
    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;

    JTX_NUM_ONLY_T
    using Point3 = Vec3<T>;
    typedef Point3<int> Point3i;
    typedef Point3<float> Point3f;
    typedef Point3<double> Point3d;

    JTX_NUM_ONLY_T
    using Normal3 = Vec3<T>;
    typedef Normal3<int> Normal3i;
    typedef Normal3<float> Normal3f;
    typedef Normal3<double> Normal3d;
    //endregion

    JTX_NUM_ONLY_T
    JTX_HOST JTX_INLINE std::string toString(const Vec3<T> &vec) {
        return "Vec3(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
    }
    //endregion
}// namespace jtx
