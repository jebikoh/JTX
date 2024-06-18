#pragma once

#include "./vec3.hpp"
#include "./vecmath.hpp"
#include "./constants.hpp"

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
}