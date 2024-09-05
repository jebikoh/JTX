#pragma once
#include <jtxlib/math/math.hpp>

namespace jtx {
    float blackBody(float lambda, float temp) {
        if (temp <= 0) return 0;

        const float c = 299792458.0f;
        const float h = 6.62606957e-34f;
        const float kb = 1.3806488e-23f;

        float l = lambda * 1e-9f;
        return (2 * h * c * c) / (pow<5>(l) * (fastExp((h * c) / (l * kb * temp)) - 1));
    }
}