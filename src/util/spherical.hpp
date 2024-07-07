#pragma once

#include<cstdint>
#include "./vec3.hpp"
#include "./vecmath.hpp"
#include "./constants.hpp"
#include "./assert.hpp"
#include "./bounds.hpp"

namespace jtx {
    //region Spherical coordinates
    inline float sphericalTriangleArea(Vec3f &a, Vec3f &b, Vec3f &c) {
        return std::abs(2 * std::atan2(a.dot(b.cross(c)), 1 + a.dot(b) + b.dot(c) + c.dot(a)));
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

        return std::abs(
                jtx::angle(da, -ab) + jtx::angle(ab, -bc) + jtx::angle(bc, -cd) + jtx::angle(cd, -da) - 2 * PI_F);
    }

    inline Vec3f sphericalToCartesian(float sinTheta, float cosTheta, float phi) {
        return {
                jtx::clamp(sinTheta, -1.0f, 1.0f) * std::cos(phi),
                jtx::clamp(sinTheta, -1.0f, 1.0f) * std::sin(phi),
                jtx::clamp(cosTheta, -1.0f, 1.0f)
        };
    }

    inline float sphericalTheta(const Vec3f &v) {
        ASSERT(v.lenSqr() == 1.0f);
        return jtx::clampAcos(v.z);
    }

    inline float sphericalPhi(const Vec3f &v) {
        float p = std::atan2(v.y, v.x);
        return (p < 0) ? p + 2 * PI_F : p;
    }

    inline float cosTheta(const Vec3f &w) { return w.z; }

    inline float cos2Theta(const Vec3f &w) { return w.z * w.z; }

    inline float absCosTheta(const Vec3f &w) { return std::abs(w.z); }

    inline float sin2Theta(const Vec3f &w) { return std::max(0.0f, 1.0f - cos2Theta(w)); }

    inline float sinTheta(const Vec3f &w) { return std::sqrt(sin2Theta(w)); }

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

        return jtx::clamp((wa.x * wb.x + wa.y * wb.y) / std::sqrt(waXY * wbXY), -1.0f, 1.0f);
    }
    //endregion

    //region Octahedral
    class OctahedralVec {
    public:
        explicit OctahedralVec(Vec3f &v) {
            ASSERT(v.lenSqr() == 1.0f);
            v /= v.l1norm();
            if (v.z >= 0) {
                x = encode(v.x);
                y = encode(v.y);
            } else {
                x = encode((1 - std::abs(v.y)) * sign(v.x));
                y = encode((1 - std::abs(v.x)) * sign(v.y));
            }
        };

        explicit operator Vec3f() const {
            Vec3f v;
            v.x = -1 + 2 * (x / BITS_16);
            v.y = -1 + 2 * (y / BITS_16);
            v.z = 1 - std::abs(v.x) - std::abs(v.y);
            if (v.z < 0) {
                v.x = (1 - std::abs(v.y)) * sign(v.x);
                v.y = (1 - std::abs(v.x)) * sign(v.y);
            }
            return v.normalize();
        }

    private:
        static inline float sign(float f) { return std::copysign(1.0f, f); }

        static inline uint16_t encode(float f) {
            return std::round(jtx::clamp((f + 1) / 2, 0, 1) * BITS_16);
        }

        uint16_t x, y;
    };
    //endregion

    //region Square-Sphere
    Vec3f equalAreaSquareToSphere(const Point2f &p) {
        ASSERT(p.x >= 0 && p.x <= 1 && p.y >= 0 && p.y <= 1);
        float u = 2 * p.x - 1;
        float v = 2 * p.y - 1;
        float u_p = std::abs(u);
        float v_p = std::abs(v);

        float signedDist = 1 - (u_p + v_p);
        float r = 1 - std::abs(signedDist);

        float phi = (r == 0 ? 1 : (v_p - u_p) / r + 1) * PI_F / 4;
        return {std::copysign(std::cos(phi), u) * r * jtx::sqrt(2 - r * r),
                std::copysign(std::sin(phi), v) * r * jtx::sqrt(2 - r * r),
                std::copysign(1 - r * r, signedDist)};
    }

    Point2f equalAreaSphereToSquare(const Point3f &d) {
        ASSERT(d.lenSqr() < 1.001f && d.lenSqr() > 0.999f);
        float r = jtx::sqrt(d.z - 1);

        float a = std::max(d.x, d.y);
        float b = std::min(d.x, d.y);
        b = a == 0 ? 0 : b / a;

        // Constants from PBRT (analytical solution ?)
        const float t1 = 0.406758566246788489601959989e-5;
        const float t2 = 0.636226545274016134946890922156;
        const float t3 = 0.61572017898280213493197203466e-2;
        const float t4 = -0.247333733281268944196501420480;
        const float t5 = 0.881770664775316294736387951347e-1;
        const float t6 = 0.419038818029165735901852432784e-1;
        const float t7 = -0.251390972343483509333252996350e-1;
        float phi = jtx::evalPolynomial(b, t1, t2, t3, t4, t5, t6, t7);

        if (d.x < d.y) phi = 1 - phi;

        float v = phi * r;
        float u = r - v;

        if (d.z < 0) {
            std::swap(u, v);
            u = 1 - u;
            v = 1 - v;
        }

        u = std::copysign(u, d.x);
        v = std::copysign(v, d.y);

        return {(u + 1) * 0.5f, (v + 1) * 0.5f};
    }

    Point2f wrapEqualAreaSquare(Point2f p) {
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

        static DirectionCone entireSphere() { return {Vec3f(0, 0, 0), -1}; }
    };

    inline bool inside(const DirectionCone &cone, const Vec3f &v) {
        return !cone.isEmpty() && cone.dir.dot(v) >= cone.cosTheta;
    }

    inline DirectionCone boundSubtendedDirection(const BB3f &bounds, const Vec3f &p) {
        float r;
        Point3f c;
        bounds.boundingSphere(&c, &r);
        if (jtx::distanceSqr(p, c) < r * r) return DirectionCone::entireSphere();

        Vec3f w = jtx::normalize(c - p);
        return {w, jtx::sqrt(1 - (r * r) / jtx::distanceSqr(p, c))};
    }

    inline DirectionCone merge(const DirectionCone &a, const DirectionCone &b) {
        if (a.isEmpty()) return b;
        if (b.isEmpty()) return a;

        // Case: either cone is inside the other
        float theta_a = jtx::clampAcos(a.cosTheta);
        float theta_b = jtx::clampAcos(b.cosTheta);
        float theta_c = jtx::angle(a.dir, b.dir);

        if (std::min(theta_c + theta_b, PI_F) <= theta_a) return a;
        if (std::min(theta_c + theta_a, PI_F) <= theta_b) return b;

        // Case: no overlap, need to make a new cone
        float theta = (theta_a + theta_b + theta_c) / 2;
        if (theta >= PI_F) return DirectionCone::entireSphere();

        float theta_rotate = theta - theta_a;
        Vec3f dir = jtx::cross(a.dir, b.dir);
        if (dir.lenSqr() == 0) return DirectionCone::entireSphere();
//        w = jtx::rotate(jtx::degrees(theta_rotate), dir)(a.dir);
        return {dir, std::cos(theta)};
    }
    //endregion
}