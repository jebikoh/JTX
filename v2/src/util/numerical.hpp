/**
 * This file contains numerical utility functions primarily used by debug asserts
 */

#pragma once

#include <stdexcept>
#include <cmath>

#define JTX_NUM_ONLY template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
#define JTX_FP_ONLY template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
#define JTX_INT_ONLY template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>

#define JTX_FP_BOOL typename std::enable_if_t<std::is_floating_point_v<T>, bool>
#define JTX_FP_T typename std::enable_if_t<std::is_floating_point_v<T>, T>
#define JTX_INT_BOOL typename std::enable_if_t<std::is_integral_v<T>, bool>
#define JTX_INT_T typename std::enable_if_t<std::is_integral_v<T>, T>

namespace jtx {
    template<typename T>
    inline
    JTX_FP_BOOL
    isNaN(T v) {
        return std::isnan(v);
    }

    template<typename T>
    inline
    JTX_INT_BOOL
    isNaN(T v) {
        return false;
    }

    template<typename T>
    inline
    JTX_FP_T
    ceil(T v) {
        return std::ceil(v);
    }

    template<typename T>
    inline
    JTX_INT_T
    ceil(T v) {
        return v;
    }

    template<typename T>
    inline
    JTX_FP_T
    floor(T v) {
        return std::floor(v);
    }

    template<typename T>
    inline
    JTX_INT_T
    floor(T v) {
        return v;
    }
} // jtx
