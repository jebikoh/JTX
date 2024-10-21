#pragma once

#include <jtxlib.hpp>
#include <jtxlib/math/math.hpp>
#include <jtxlib/math/numerical.hpp>
#include <jtxlib/math/vec2.hpp>
#include <jtxlib/math/vec3.hpp>
#include <jtxlib/math/vec4.hpp>

namespace jtx {
    //region Dot Product
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T dot(const Vec2<T> &a, const Vec2<T> &b) {
        return a.x * b.x + a.y * b.y;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T dot(const Vec3<T> &a, const Vec3<T> &b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T dot(const Vec4<T> &a, const Vec4<T> &b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }
    //endregion

    //region ABS
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> abs(const Vec2<T> &v) {
        return {jtx::abs(v.x), jtx::abs(v.y)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> abs(const Vec3<T> &v) {
        return {jtx::abs(v.x), jtx::abs(v.y), jtx::abs(v.z)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec4<T> abs(const Vec4<T> &v) {
        return {jtx::abs(v.x), jtx::abs(v.y), jtx::abs(v.z), jtx::abs(v.w)};
    }
    //endregion

    //region ABS Dot Product
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T absdot(const Vec2<T> &a, const Vec2<T> &b) {
        return jtx::abs(a.dot(b));
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T absdot(const Vec3<T> &a, const Vec3<T> &b) {
        return jtx::abs(a.dot(b));
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T absdot(const Vec4<T> &a, const Vec4<T> &b) {
        return jtx::abs(a.dot(b));
    }
    //endregion

    //region Normalize
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> normalize(const Vec2<T> &v) {
        float l = v.len();
        if (l != 0) {
            return v / l;
        } else {
            return Vec2<T>{};
        }
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> normalize(const Vec3<T> &v) {
        float l = v.len();
        if (l != 0) {
            return v / l;
        } else {
            return Vec3<T>{};
        }
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec4<T> normalize(const Vec4<T> &v) {
        float l = v.len();
        if (l != 0) {
            return v / l;
        } else {
            return Vec4<T>{};
        }
    }
    //endregion

    //region Ceil & Floor
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> ceil(const Vec2<T> &v) {
        return {jtx::ceil(v.x), jtx::ceil(v.y)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> ceil(const Vec3<T> &v) {
        return {jtx::ceil(v.x), jtx::ceil(v.y), jtx::ceil(v.z)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec4<T> ceil(const Vec4<T> &v) {
        return {jtx::ceil(v.x), jtx::ceil(v.y), jtx::ceil(v.z), jtx::ceil(v.w)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> floor(const Vec2<T> &v) {
        return {jtx::floor(v.x), jtx::floor(v.y)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> floor(const Vec3<T> &v) {
        return {jtx::floor(v.x), jtx::floor(v.y), jtx::floor(v.z)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec4<T> floor(const Vec4<T> &v) {
        return {jtx::floor(v.x), jtx::floor(v.y), jtx::floor(v.z), jtx::floor(v.w)};
    }
    //endregion

    //region Min & Max
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> min(const Vec2<T> &a, const Vec2<T> &b) {
        return {std::min(a.x, b.x), std::min(a.y, b.y)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> min(const Vec3<T> &a, const Vec3<T> &b) {
        return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec4<T> min(const Vec4<T> &a, const Vec4<T> &b) {
        return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> max(const Vec2<T> &a, const Vec2<T> &b) {
        return {std::max(a.x, b.x), std::max(a.y, b.y)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> max(const Vec3<T> &a, const Vec3<T> &b) {
        return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec4<T> max(const Vec4<T> &a, const Vec4<T> &b) {
        return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)};
    }
    //endregion

    //region Horizontal Product
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T hprod(const Vec2<T> &v) {
        return v.x * v.y;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T hprod(const Vec3<T> &v) {
        return v.x * v.y * v.z;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE T hprod(const Vec4<T> &v) {
        return v.x * v.y * v.z * v.w;
    }
    //endregion

    //region LERP
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE auto lerp(const Vec2<T> &a, const Vec2<T> &b, float t) {
        return (1 - t) * a + b * t;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE auto
    lerp(const Vec3<T> &a, const Vec3<T> &b, float t) {
        return (1 - t) * a + b * t;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE auto lerp(const Vec4<T> &a, const Vec4<T> &b, float t) {
        return (1 - t) * a + b * t;
    }
    //endregion

    //region FMA
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> fma(const Vec2<T> &a, const Vec2<T> &b, const Vec2<T> &c) {
        return a * b + c;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> fma(const Vec3<T> &a, const Vec3<T> &b, const Vec3<T> &c) {
        return a * b + c;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec4<T> fma(const Vec4<T> &a, const Vec4<T> &b, const Vec4<T> &c) {
        return a * b + c;
    }
    //endregion

    //region Angle between
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float angle(const Vec2<T> &a, const Vec2<T> &b) {
        if (a.dot(b) < 0) {
            return PI_F - 2 * jtx::clampAsin((a - b).len() / 2);
        }
        return 2 * jtx::clampAsin((a - b).len() / 2);
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float angle(const Vec3<T> &a, const Vec3<T> &b) {
        if (a.dot(b) < 0) {
            return PI_F - 2 * jtx::clampAsin((a - b).len() / 2);
        }
        return 2 * jtx::clampAsin((a - b).len() / 2);
    }
    //endregion

    //region Gram-Schmidt
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec2<T> gramSchmidt(const Vec2<T> &a, const Vec2<T> &b) {
        return a - (b * a.dot(b));
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> gramSchmidt(const Vec3<T> &a, const Vec3<T> &b) {
        return a - (b * a.dot(b));
    }
    //endregion

    //region Distance
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float distanceSqr(const Vec2<T> &a, const Vec2<T> &b) {
        return (a - b).lenSqr();
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float distanceSqr(const Vec3<T> &a, const Vec3<T> &b) {
        return (a - b).lenSqr();
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float distanceSqr(const Vec4<T> &a, const Vec4<T> &b) {
        return (a - b).lenSqr();
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float distance(const Vec2<T> &a, const Vec2<T> &b) {
        return (a - b).len();
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float distance(const Vec3<T> &a, const Vec3<T> &b) {
        return (a - b).len();
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE float distance(const Vec4<T> &a, const Vec4<T> &b) {
        return (a - b).len();
    }
    //endregion

    //region Vec3 Specific
    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> cross(const Vec3<T> &a, const Vec3<T> &b) {
        return {jtx::dop(a.y, b.z, a.z, b.y),
                jtx::dop(a.z, b.x, a.x, b.z),
                jtx::dop(a.x, b.y, a.y, b.x)};
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> align(const Vec3<T> &a, const Vec3<T> &b) {
        return (a.dot(b) < 0.0f) ? -a : a;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> reflect(const Vec3<T> &v, const Vec3<T> &n) {
        return v - 2 * dot(v, n) * n;
    }

    JTX_NUM_ONLY_T
    JTX_HOSTDEV JTX_INLINE Vec3<T> refract(const Vec3<T> &uv, const Vec3<T> &n, T etai_over_etat) {
        auto cos_theta = ::fminf(jtx::dot(-uv, n), 1.0);
        auto r_out_perp = etai_over_etat * (uv + cos_theta * n);
        auto r_out_prll = -::sqrtf(::fabs(1.0 - r_out_perp.lenSqr())) * n;
        return r_out_perp + r_out_prll;
    }
    //endregion
}// namespace jtx