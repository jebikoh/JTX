#pragma once
#include <jtxlib/math/math.hpp>
#include <jtxlib/util/taggedptr.hpp>
#include <jtxlib/std/memory_resource.hpp>
#include <jtxlib/std/std.hpp>

namespace jtx {

    static constexpr int N_SPECTRUM_SAMPLES = 4;

    class SampledSpectrum {
    public:
        JTX_HOSTDEV
        explicit SampledSpectrum(const float c) { data.fill(c); }


    private:
        array<float, N_SPECTRUM_SAMPLES> data;
    };

    class SampledWavelengths;

    class ConstantSpectrum;

    class Spectrum : public jtx::TaggedPtr<ConstantSpectrum> {
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

    class ConstantSpectrum {
    public:
        JTX_HOSTDEV
        explicit ConstantSpectrum(const float c) : c(c) {}

        JTX_HOSTDEV
        float operator()(float lambda) const { return c; }

        [[nodiscard]]
        JTX_HOSTDEV
        float maxValue() const { return c; }
    private:
        float c;
    };

    class DenselySampledSpectrum {};

    class PiecewiseLinearSpectrum {};

    class BlackbodySpectrum {};
}