#pragma once

#include <limits>
#include <jtxlib.hpp>

namespace jtx {
    // TODO: expand as needed
    // Structure from https://github.com/behindthepixels/EDXUtil/
    struct Zero {
        JTX_HOSTDEV inline explicit operator int() const { return 0; }

        JTX_HOSTDEV inline explicit operator float() const { return 0.0f; }

        JTX_HOSTDEV inline explicit operator double() const { return 0.0; }

        template<typename T>
        JTX_HOSTDEV inline bool operator==(const T &other) const {
            return static_cast<T>(*this) == other;
        }

        template<typename T>
        JTX_HOSTDEV inline bool operator!=(const T &other) const {
            return static_cast<T>(*this) != other;
        }
    };

    #if defined(CUDA_ENABLED) && defined(__CUDA_ARCH__)
        __constant__ Zero JTX_ZERO;
    #else
        constexpr Zero JTX_ZERO;
    #endif

    constexpr double PI = 3.14159265358979323846;
    constexpr float PI_F = 3.14159265358979323846f;
    constexpr float BITS_16 = 65535.0f;

    constexpr float INFINITY_F = std::numeric_limits<float>::infinity();
    constexpr double INFINITY_D = std::numeric_limits<double>::infinity();

    constexpr float NEG_INFINITY_F = -std::numeric_limits<float>::infinity();
    constexpr double NEG_INFINITY_D = -std::numeric_limits<double>::infinity();
}

