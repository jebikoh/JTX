#pragma once

#include <cmath>
#include <algorithm>

namespace jtx {
    inline float clampAsin(float theta) {
        return std::asin(std::clamp(theta, -1.0f, 1.0f));
    }

    inline float clampAcos(float theta) {
        return std::acos(std::clamp(theta, -1.0f, 1.0f));
    }

    inline double clampAsin(double theta) {
        return std::asin(std::clamp(theta, -1.0, 1.0));
    }

    inline double clampAcos(double theta) {
        return std::acos(std::clamp(theta, -1.0, 1.0));
    }

    inline float radians(float deg) {
        return deg * PI_F / 180.0f;
    }

    inline float degrees(float rad) {
        return rad * 180.0f / PI_F;
    }

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline
    T
    fma(T a, T b, T c) {
        return a * b + c;
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_floating_point_v<T>, T>
    dop(T a, T b, T c, T d) {
        auto cd = c * d;
        auto alpha = jtx::fma(a, b, -cd);
        auto beta = jtx::fma(-c, d, cd);
        return alpha + beta;
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_integral_v<T>, T>
    dop(T a, T b, T c, T d) {
        return a * b - c * d;
    }
}