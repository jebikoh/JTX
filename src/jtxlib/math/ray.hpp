#pragma once

#include <jtxlib/math/numerical.hpp>
#include <jtxlib/math/vec3.hpp>
#include <jtxlib/math/vecmath.hpp>
#include <jtxlib.hpp>
#include "mat4.hpp"

namespace jtx {

    JTX_NUM_ONLY_T
    class Ray {
    public:
        Point3<T> origin;
        Vec3<T> dir;
        T time;
        // Add medium later

        [[nodiscard]] JTX_INLINE bool valid() const {
            return origin.valid() && dir.valid() && !jtx::isNaN(time);
        }

        //region Constructors
        JTX_DEV Ray() : origin(), dir(), time(JTX_ZERO) {}

        JTX_DEV Ray(const Point3<T> &origin, const Vec3<T> &direction, T time = T(0))
                : origin(origin), dir(direction), time(time) {
            ASSERT(valid());
        }

        JTX_DEV Ray(const Ray &other) : origin(other.origin), dir(other.dir), time(other.time) {
            ASSERT(valid());
        }

        ~Ray() = default;
        //endregion

        [[nodiscard]] JTX_DEV JTX_INLINE Point3<T> at(T t) const {
            return origin + t * dir;
        }
    };

    JTX_NUM_ONLY_T
    class RayDifferential : public Ray<T> {
    public:
        Point3<T> rxOrigin, ryOrigin;
        Vec3<T> rxDirection, ryDirection;
        bool hasDiffs;

        [[nodiscard]] JTX_INLINE bool valid() const {
            return Ray<T>::valid() &&
                   (!hasDiffs || (rxOrigin.valid() && ryOrigin.valid() && rxDirection.valid() && ryDirection.valid()));
        }

        //region Constructors
        JTX_DEV RayDifferential() : Ray<T>(), rxOrigin(), ryOrigin(), rxDirection(), ryDirection(), hasDiffs(false) {}

        JTX_DEV RayDifferential(const Point3<T> &origin, const Vec3<T> &direction, T time = T(0))
                : Ray<T>(origin, direction, time), rxOrigin(), ryOrigin(), rxDirection(), ryDirection(),
                  hasDiffs(false) {
            ASSERT(valid());
        }

        JTX_DEV explicit RayDifferential(const Ray<T> &ray) : Ray<T>(ray), rxOrigin(), ryOrigin(), rxDirection(),
                                                              ryDirection(),
                                                              hasDiffs(false) {
            ASSERT(valid());
        }

        JTX_DEV RayDifferential(const RayDifferential &other) : Ray<T>(other), rxOrigin(other.rxOrigin),
                                                                ryOrigin(other.ryOrigin),
                                                                rxDirection(other.rxDirection),
                                                                ryDirection(other.ryDirection),
                                                                hasDiffs(other.hasDiffs) {
            ASSERT(valid());
        }
        //endregion

        JTX_DEV JTX_INLINE void scale(T s) {
            rxOrigin = this->origin + (rxOrigin - this->origin) * s;
            ryOrigin = this->origin + (ryOrigin - this->origin) * s;
            rxDirection = this->dir + (rxDirection - this->dir) * s;
            ryDirection = this->dir + (ryDirection - this->dir) * s;
        }
    };

    [[maybe_unused]] typedef Ray<float> Rayf;
    [[maybe_unused]] typedef Ray<double> Rayd;

    typedef RayDifferential<float> RayfDifferential;
    typedef RayDifferential<double> RaydDifferential;

    JTX_NUM_ONLY_T
    JTX_HOST JTX_INLINE std::string toString(const Ray<T> &ray) {
        return jtx::to_string(ray.origin) + " + t * " + jtx::to_string(ray.dir) + " (t = " + std::to_string(ray.time) +
               ")";
    }
}// namespace jtx
