#pragma once

#include "./assert.hpp"
#include "./math.hpp"
#include "./numerical.hpp"
#include "./vec2.hpp"
#include "./vec3.hpp"
#include "./vecmath.hpp"
#include <iostream>

namespace jtx {

    JTX_NUM_ONLY_T
    class AABB3 {
    public:
        Point3<T> pmin, pmax;

        // "empty" = "no volume"
        [[nodiscard]] inline bool isEmpty() const { return pmin.x >= pmax.x || pmin.y >= pmax.y || pmin.z >= pmax.z; }

        [[nodiscard]] inline bool isDegenerate() const { return pmin.x > pmax.x || pmin.y > pmax.y || pmin.z > pmax.z; }

        //region Constructors
        AABB3() {
            std::cout << "Default constructor called" << std::endl;
            T minval = std::numeric_limits<T>::lowest();
            T maxval = std::numeric_limits<T>::max();

            pmin = {maxval, maxval, maxval};
            pmax = {minval, minval, minval};
        }

        AABB3(const Point3<T> &a, const Point3<T> &b) {
            std::cout << "Two point constructor called" << std::endl;
            pmin = jtx::min(a, b);
            pmax = jtx::max(a, b);
        }

        explicit AABB3(const Point3<T> &p) : pmin(p), pmax(p) {
            std::cout << "Point constructor called" << std::endl;
        }

        AABB3(const AABB3 &other) {
            std::cout << "Copy constructor called (sametype)" << std::endl;
            pmin = Point3<T>(other.pmin);
            pmax = Point3<T>(other.pmax);
        }

        JTX_NUM_ONLY(U)
        explicit AABB3(const AABB3<U> &other) {
            std::cout << "Copy constructor called" << std::endl;
            if (other.isEmpty()) {
                *this = AABB3<T>();
            } else {
                pmin = Point3<T>(other.pmin);
                pmax = Point3<T>(other.pmax);
            }
        }

        ~AABB3() = default;
        //endregion

        //region Member functions
        // Modified from https://pbr-book.org/4ed/Geometry_and_Transformations/Bounding_Boxes
        [[nodiscard]] inline Point3<T> corner(int i) const {
            ASSERT(i >= 0 && i < 8);
            return Point3<T>(i & 1 ? pmax.x : pmin.x,
                             i & 2 ? pmax.y : pmin.y,
                             i & 4 ? pmax.z : pmin.z);
        }

        inline AABB3 &merge(const Point3<T> &p) {
            pmin = jtx::min(pmin, p);
            pmax = jtx::max(pmax, p);
            return *this;
        }

        inline AABB3 &merge(const AABB3 &b) {
            pmin = jtx::min(pmin, b.pmin);
            pmax = jtx::max(pmax, b.pmax);
            return *this;
        }

        inline bool overlaps(const AABB3 &b) const {
            return pmin.x <= b.pmax.x && pmax.x >= b.pmin.x &&
                   pmin.y <= b.pmax.y && pmax.y >= b.pmin.y &&
                   pmin.z <= b.pmax.z && pmax.z >= b.pmin.z;
        }

        inline bool inside(const Point3<T> &p) const {
            return p.x >= pmin.x && p.x <= pmax.x &&
                   p.y >= pmin.y && p.y <= pmax.y &&
                   p.z >= pmin.z && p.z <= pmax.z;
        }

        inline bool insideExclusive(const Point3<T> &pt) const {
            return pt.x > pmin.x && pt.x < pmax.x &&
                   pt.y > pmin.y && pt.y < pmax.y &&
                   pt.z > pmin.z && pt.z < pmax.z;
        }

        inline AABB3 &expand(T delta) {
            ASSERT(delta >= 0);
            pmin -= delta;
            pmax += delta;
            return *this;
        }

        inline AABB3 &shrink(T delta) {
            ASSERT(delta >= 0);
            pmin += delta;
            pmax -= delta;
            return *this;
        }

        inline Vec3<T> diagonal() const {
            return pmax - pmin;
        }

        inline T surfaceArea() const {
            Vec3<T> d = diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }

        inline T volume() const {
            Vec3<T> d = diagonal();
            return d.x * d.y * d.z;
        }

        [[nodiscard]] inline int maxDim() const {
            Vec3<T> d = diagonal();
            if (d.x > d.y && d.x > d.z) return 0;
            else if (d.y > d.z)
                return 1;
            else
                return 2;
        }

        [[nodiscard]] inline Point3f lerp(const Point3f &t) const {
            return Point3f(jtx::lerp(pmin.x, pmax.x, t.x),
                           jtx::lerp(pmin.y, pmax.y, t.y),
                           jtx::lerp(pmin.z, pmax.z, t.z));
        }

        inline Vec3f offset(Point3f &p) const {
            Vec3f o = p - pmin;
            if (pmax.x > pmin.x) o.x /= pmax.x - pmin.x;
            if (pmax.y > pmin.y) o.y /= pmax.y - pmin.y;
            if (pmax.z > pmin.z) o.z /= pmax.z - pmin.z;
            return o;
        }

        inline void boundingSphere(Point3<T> *center, T *radius) const {
            *center = (pmin + pmax) / 2;
            // PBRT: when would the center be outside the box?
            *radius = inside(*center) ? distance(*center, pmax) : 0;
        }
        //endregion
    };

    //region AABB3 functions
    JTX_NUM_ONLY_T
    inline AABB3<T> merge(const AABB3<T> &a, const AABB3<T> &b) {
        AABB3<T> res;
        res.pmin = jtx::min(a.pmin, b.pmin);
        res.pmax = jtx::max(a.pmax, b.pmax);
        return res;
    }

    JTX_NUM_ONLY_T
    inline AABB3<T> merge(const AABB3<T> &a, const Point3<T> &p) {
        AABB3<T> res;
        res.pmin = jtx::min(a.pmin, p);
        res.pmax = jtx::max(a.pmax, p);
        return res;
    }

    JTX_NUM_ONLY_T
    inline AABB3<T> intersect(const AABB3<T> &a, const AABB3<T> &b) {
        AABB3<T> res;
        res.pmin = jtx::max(a.pmin, b.pmin);
        res.pmax = jtx::min(a.pmax, b.pmax);
        return res;
    }

    JTX_NUM_ONLY_T
    inline bool overlaps(const AABB3<T> &a, const AABB3<T> &b) {
        return a.overlaps(b);
    }

    // Added these because the syntax a.inside(p) is semantically confusing
    JTX_NUM_ONLY_T
    inline bool inside(const Point3<T> &p, const AABB3<T> &a) {
        return a.inside(p);
    }

    JTX_NUM_ONLY_T
    inline bool insideExclusive(const Point3<T> &p, const AABB3<T> &a) {
        return a.insideExclusive(p);
    }

    template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>>>
    inline auto distanceSqr(const AABB3<T> &b, const Point3<U> &p) {
        using TmU = decltype(T{} - U{});
        TmU dx = std::max<TmU>({0, b.pmin.x - p.x, p.x - b.pmax.x});
        TmU dy = std::max<TmU>({0, b.pmin.y - p.y, p.y - b.pmax.y});
        TmU dz = std::max<TmU>({0, b.pmin.z - p.z, p.z - b.pmax.z});
        return dx * dx + dy * dy + dz * dz;
    }

    template<typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T> && std::is_arithmetic_v<U>>>
    inline auto distance(const AABB3<T> &b, const Point3<U> &p) {
        return std::sqrt(distanceSqr(b, p));
    }

    JTX_NUM_ONLY_T
    inline AABB3<T> expand(const AABB3<T> &a, T delta) {
        ASSERT(delta >= 0);
        AABB3<T> res;
        res.pmin = a.pmin - delta;
        res.pmax = a.pmax + delta;
        return res;
    }

    JTX_NUM_ONLY_T
    inline AABB3<T> shrink(const AABB3<T> &a, T delta) {
        ASSERT(delta >= 0);
        AABB3<T> res;
        res.pmin = a.pmin + delta;
        res.pmax = a.pmax - delta;
        return res;
    }
    //endregion

    typedef AABB3<int> BB3i;
    typedef AABB3<float> BB3f;
}// namespace jtx
