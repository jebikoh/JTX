#pragma once
#include <jtxlib/math/vec3.hpp>

namespace jtx {
    class Quaternion {
    public:
        float w;
        Vec3f v;

        //region Constructors
        /**
         * Returns an identity quaternion
         */
        JTX_HOSTDEV Quaternion() : w(1), v(0, 0, 0) {}
        JTX_HOSTDEV Quaternion(float w, const Vec3f& v) : w(w), v(v) {}
        JTX_HOSTDEV Quaternion(float w, float x, float y, float z) : w(w), v(x, y, z) {}

        JTX_HOSTDEV static Quaternion pure(const Vec3f& v) { return {0, v}; }
        JTX_HOSTDEV static Quaternion real(float w) { return {w, 0, 0, 0}; }
        //endregion

        //region Operators
        JTX_HOSTDEV Quaternion operator+(const Quaternion& q) const { return {w + q.w, v + q.v}; }
        JTX_HOSTDEV Quaternion operator-(const Quaternion& q) const { return {w - q.w, v - q.v}; }
        JTX_HOSTDEV Quaternion operator-() const { return {-w, -v}; }
        JTX_HOSTDEV Quaternion operator*(const Quaternion &q) const { return {w * q.w - v.dot(q.v), w * q.v + q.w * v + v.cross(q.v)}; }
        JTX_HOSTDEV Quaternion operator*(const float s) const { return {w * s, v * s}; }
        JTX_HOSTDEV Quaternion operator/(const float s) const { ASSERT(s > 0.0f); return {w / s, v / s}; }

        JTX_HOSTDEV Quaternion &operator+=(const Quaternion& q) { w += q.w; v += q.v; return *this; }
        JTX_HOSTDEV Quaternion &operator-=(const Quaternion& q) { w -= q.w; v -= q.v; return *this; }
        JTX_HOSTDEV Quaternion &operator*=(const Quaternion& q) { *this = *this * q; return *this; }

        JTX_HOSTDEV Quaternion &operator*=(const float s) { w *= s; v *= s; return *this; }
        JTX_HOSTDEV Quaternion &operator/=(const float s) { ASSERT(s > 0.0f); w /= s; v /= s; return *this; }

        JTX_HOSTDEV friend Quaternion operator*(const float s, const Quaternion& q) { return q * s; }
        //endregion

        //region Member functions
        [[nodiscard]] JTX_HOSTDEV float dot(const Quaternion &q) const { return w * q.w + v.dot(q.v); }
        [[nodiscard]] JTX_HOSTDEV float len() const { return jtx::sqrt((*this).dot(*this)); }
        [[nodiscard]] JTX_HOSTDEV Quaternion normalize() { ASSERT(len() > 0.0f); (*this) /= len(); return *this; }
        [[nodiscard]] JTX_HOSTDEV Quaternion conjugate() const { return {w, -v}; }
        [[nodiscard]] JTX_HOSTDEV Quaternion inverse() const { return conjugate() / dot(*this); }

        /**
         * Calculates the angle between this and another quaternion
         * Assumes both quaternions are normalized
         * @param q Other quaternion
         * @return Angle between this and q
         */
        [[nodiscard]] JTX_HOSTDEV float angle(const Quaternion &q) const {
            // This is what PBRT does
            // http://www.plunk.org/~hatch/rightway.html
            float theta = 2.0f * jtx::clampAsin((q - (*this)).len() / 2);
            if (dot(q) < 0) return jtx::PI_F - theta;
            return theta;
        }
        //endregion
    };

    //region In-line Functions
    JTX_HOSTDEV JTX_INLINE float dot(const Quaternion &q1, const Quaternion &q2) { return q1.dot(q2); }
    JTX_HOSTDEV JTX_INLINE Quaternion normalize(const Quaternion &q) { return q / q.len(); }
    JTX_HOSTDEV JTX_INLINE float angle(const Quaternion &q1, const Quaternion &q2) { return q1.angle(q2); }

    JTX_HOSTDEV JTX_INLINE Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t) {
        // One again: http://www.plunk.org/~hatch/rightway.html
        float theta = q1.angle(q2);
        float sxoxTheta = sinXOverX(theta);
        return (sinXOverX(1 - t * theta) / sxoxTheta) * (1 - t) * q1 + (sinXOverX(t * theta) / sxoxTheta) * t * q2;
    }
    //endregion
}