#pragma once
#include "jtxlib/util/taggedptr.hpp"


#include <jtxlib/math/math.hpp>
#include <jtxlib/std/memory_resource.hpp>

namespace jtx {

    class SampledSpectrum{};
    class SampledWavelengths{};

    class Spectrum : public jtx::TaggedPtr<> {
    public:
        using TaggedPtr::TaggedPtr;

        JTX_HOSTDEV
        float operator()(float lambda) const {
            auto op = [&](auto ptr) { return (*ptr)(lambda); };
            return dispatch(op);
        }

        [[nodiscard]]
        JTX_HOSTDEV
        float maxValue() const {
            auto op = [&](auto ptr) { return ptr->maxValue(); };
            return dispatch(op);
        }

        JTX_HOSTDEV
        SampledSpectrum sample(const SampledWavelengths &lambda) const {
            auto op = [&](auto ptr) { return ptr->sample(lambda); };
            return dispatch(op);
        }

        [[nodiscard]]
        JTX_HOST
        std::string toString() const {
            if (getPtr() == nullptr) return "(nullptr)";

            auto op = [&](auto ptr) { return ptr->toString(); };
            return dispatch(op);
        }
    };

    //endregion

    float blackBody(float lambda, float temp) {
        if (temp <= 0) return 0;

        const float c = 299792458.0f;
        const float h = 6.62606957e-34f;
        const float kb = 1.3806488e-23f;

        float l = lambda * 1e-9f;
        return (2 * h * c * c) / (pow<5>(l) * (fastExp((h * c) / (l * kb * temp)) - 1));
    }
}