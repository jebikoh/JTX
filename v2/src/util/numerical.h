/**
 * This file contains numerical utility functions primarily used by debug asserts
 */

#pragma once

#include <stdexcept>
#include <cmath>

namespace jtx {
    template<typename T>
    inline
    typename std::enable_if_t<std::is_floating_point_v<T>, bool>
    isNaN(T v) {
        return std::isnan(v);
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_integral_v<T>, bool>
    isNaN(T v) {
        return false;
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_floating_point_v<T>, T>
    ceil(T v) {
        return std::ceil(v);
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_integral_v<T>, T>
    ceil(T v) {
        return v;
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_floating_point_v<T>, T>
    floor(T v) {
        return std::floor(v);
    }

    template<typename T>
    inline
    typename std::enable_if_t<std::is_integral_v<T>, T>
    floor(T v) {
        return v;
    }
} // jtx
