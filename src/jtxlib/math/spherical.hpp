#pragma once

#include<cstdint>
#include <jtxlib/math/vec3.hpp>
#include <jtxlib/math/vecmath.hpp>
#include <jtxlib/math/mat4.hpp>
#include <jtxlib/math/constants.hpp>
#include <jtxlib/util/assert.hpp>
#include "./bounds.hpp"

namespace jtx {
    //region Spherical coordinates
    inline float sphericalTriangleArea(Vec3f &a, Vec3f &b, Vec3f &c) {
        return jtx::abs(2 * jtx::atan2(a.dot(b.cross(c)), 1 + a.dot(b) + b.dot(c) + c.dot(a)));
    }

    inline float sphericalQuadArea(Vec3f &a, Vec3f &b, Vec3f &c, Vec3f &d) {
        Vec3f ab = a.cross(b);
        Vec3f bc = b.cross(c);
        Vec3f cd = c.cross(d);
        Vec3f da = d.cross(a);

        if (ab.lenSqr() == 0 || bc.lenSqr() == 0 || cd.lenSqr() == 0 || da.lenSqr() == 0) return 0;

        ab.normalize();
        bc.normalize();
        cd.normalize();
        da.normalize();

        return jtx::abs(
                jtx::angle(da, -ab) + jtx::angle(ab, -bc) + jtx::angle(bc, -cd) + jtx::angle(cd, -da) - 2 * PI_F);
    }

    /**
     * Parameters should be given in radians
     */
    inline Vec3f sphericalToCartesian(float sinTheta, float cosTheta, float phi) {
        return {
                jtx::clamp(sinTheta, -1.0f, 1.0f) * jtx::cos(phi),
                jtx::clamp(sinTheta, -1.0f, 1.0f) * jtx::sin(phi),
                jtx::clamp(cosTheta, -1.0f, 1.0f)
        };
    }

    inline float sphericalTheta(const Vec3f &v) {
        ASSERT(v.lenSqr() == 1.0f);
        return jtx::clampAcos(v.z);
    }

    inline float sphericalPhi(const Vec3f &v) {
        float p = jtx::atan2(v.y, v.x);
        return (p < 0) ? p + 2 * PI_F : p;
    }

    inline float cosTheta(const Vec3f &w) { return w.z; }

    inline float cos2Theta(const Vec3f &w) { return w.z * w.z; }

    inline float absCosTheta(const Vec3f &w) { return jtx::abs(w.z); }

    inline float sin2Theta(const Vec3f &w) { return jtx::max(0.0f, 1.0f - cos2Theta(w)); }

    inline float sinTheta(const Vec3f &w) { return jtx::sqrt(sin2Theta(w)); }

    inline float tanTheta(const Vec3f &w) { return sinTheta(w) / cosTheta(w); }

    inline float tan2Theta(const Vec3f &w) { return sin2Theta(w) / cos2Theta(w); }

    inline float cosPhi(const Vec3f &w) {
        float s = sinTheta(w);
        return (s == 0) ? 1 : jtx::clamp(w.x / s, -1.0f, 1.0f);
    }

    inline float sinPhi(const Vec3f &w) {
        float s = sinTheta(w);
        return (s == 0) ? 0 : jtx::clamp(w.y / s, -1.0f, 1.0f);
    }

    inline float cosDPhi(const Vec3f &wa, const Vec3f &wb) {
        auto waXY = wa.x * wa.x + wa.y * wa.y;
        auto wbXY = wb.x * wb.x + wb.y * wb.y;
        if (waXY == 0 || wbXY == 0) return 1;

        return jtx::clamp((wa.x * wb.x + wa.y * wb.y) / jtx::sqrt(waXY * wbXY), -1.0f, 1.0f);
    }
    //endregion

    //region Octahedral
    class OctahedralVec {
    public:
        // WARNING: PBRT modified the input vector, but this version doesn't
        explicit OctahedralVec(const Vec3f &v) {
            ASSERT(jtx::equals(v.lenSqr(), 1.0f, 1e-6f));
            auto vec = v / v.l1norm();
            if (vec.z >= 0) {
                x = encode(vec.x);
                y = encode(vec.y);
            } else {
                x = encode((1 - jtx::abs(vec.y)) * sign(vec.x));
                y = encode((1 - jtx::abs(vec.x)) * sign(vec.y));
            }
        };

        explicit operator Vec3f() const {
            Vec3f v;
            v.x = -1 + 2 * (static_cast<float>(x) / BITS_16);
            v.y = -1 + 2 * (static_cast<float>(y) / BITS_16);
            v.z = 1 - jtx::abs(v.x) - jtx::abs(v.y);
            if (v.z < 0) {
                auto xo = v.x;
                v.x = (1 - jtx::abs(v.y)) * sign(xo);
                v.y = (1 - jtx::abs(xo)) * sign(v.y);
            }
            return v.normalize();
        }

    private:
        static inline float sign(float f) { return jtx::copysign(1.0f, f); }

        static inline uint16_t encode(float f) {
            return static_cast<uint16_t>(jtx::round(jtx::clamp((f + 1) / 2, 0, 1) * BITS_16));
        }

        uint16_t x, y;
    };
    //endregion

    //region Square-Sphere
    Vec3f equalAreaSquareToSphere(const Point2f &p);

    Point2f equalAreaSphereToSquare(const Point3f &d);

    inline Point2f wrapEqualAreaSquare(Point2f p) {
        if (p.x < 0) {
            p.x = -p.x;
            p.y = 1 - p.y;
        } else if (p.x > 1) {
            p.x = 2 - p.x;
            p.y = 1 - p.y;
        }
        if (p.y < 0) {
            p.x = 1 - p.x;
            p.y = -p.y;
        } else if (p.y > 1) {
            p.x = 1 - p.x;
            p.y = 2 - p.y;
        }
        return p;
    }
    //endregion

    //region DirectionCone
    class DirectionCone {
    public:
        jtx::Vec3f dir;
        float cosTheta = jtx::INFINITY_F;

        [[nodiscard]] inline bool isEmpty() const { return cosTheta == jtx::INFINITY_F; }

        //region Constructors
        DirectionCone() = default;

        DirectionCone(const Vec3f &dir, float cosTheta) : dir(jtx::normalize(dir)), cosTheta(cosTheta) {}

        explicit DirectionCone(const jtx::Vec3f &dir) : DirectionCone(dir, 1.0f) {}
        //endregion

        inline bool operator==(const DirectionCone &other) const {
            return dir == other.dir && cosTheta == other.cosTheta;
        }

        [[nodiscard]] inline bool equals(const DirectionCone &other, float epsilon) const {
            return dir.equals(other.dir, epsilon) && jtx::equals(cosTheta, other.cosTheta, epsilon);
        }

        static DirectionCone entireSphere() { return {Vec3f(0, 0, 0), -1}; }
    };

    inline bool inside(const DirectionCone &cone, const Vec3f &v) {
        return !cone.isEmpty() && cone.dir.dot(v) >= cone.cosTheta;
    }

    inline DirectionCone boundSubtendedDirection(const BBox3f &bounds, const Vec3f &p) {
        float r;
        Point3f c;
        bounds.boundingSphere(&c, &r);
        if (jtx::distanceSqr(p, c) < r * r) return DirectionCone::entireSphere();

        Vec3f w = jtx::normalize(c - p);
        return {w, jtx::safeSqrt(1 - (r * r) / jtx::distanceSqr(p, c))};
    }

    inline DirectionCone merge(const DirectionCone &a, const DirectionCone &b) {
        if (a.isEmpty()) return b;
        if (b.isEmpty()) return a;

        // Case 1: One cone is inside the other
        float theta_a = jtx::clampAcos(a.cosTheta);
        float theta_b = jtx::clampAcos(b.cosTheta);
        float theta_d = jtx::angle(a.dir, b.dir);

        if (jtx::min(theta_d + theta_b, PI_F) <= theta_a) return a;
        if (jtx::min(theta_d + theta_a, PI_F) <= theta_b) return b;

        // Case 2: New cone
        float theta_o = (theta_a + theta_b + theta_d) / 2;
        if (theta_o >= PI_F) return DirectionCone::entireSphere();

        float theta_r = theta_o - theta_a;
        Vec3f wr = jtx::cross(a.dir, b.dir);
        if (wr.lenSqr() == 0) return DirectionCone::entireSphere();
        auto w = jtx::rotate(jtx::degrees(theta_r), wr).applyToVec(a.dir);
        return {w, jtx::cos(theta_o)};
    }
    //endregion
}