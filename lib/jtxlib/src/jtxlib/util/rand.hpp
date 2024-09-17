#pragma once

#include <chrono>
#include <jtxlib/math/numerical.hpp>
#include <random>

namespace jtx {
    namespace detail {
        JTX_HOST JTX_INLINE std::mt19937 &getGenerator() {
            static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
            return generator;
        }
    }// namespace detail

    JTX_HOST JTX_INLINE void setRandomSeed(unsigned int seed) {
        detail::getGenerator().seed(seed);
    }

    JTX_NUM_ONLY_T
    JTX_HOST JTX_INLINE T random() {
        static std::uniform_real_distribution<T> distribution(0.0, 1.0);
        return distribution(detail::getGenerator());
    }

    JTX_NUM_ONLY_T
    JTX_HOST JTX_INLINE T random(T min, T max) {
        return min + (max - min) * random<T>();
    }
}// namespace jtx