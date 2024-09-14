#pragma once
#include <jtxlib/math/math.hpp>

namespace jtx {

    class SampledSpectrum {

    };

    class SampledWavelengths {

    };

    // PBRTv4 uses tagged pointers
    // Those are nice, but I went with a CRTP pattern to simplify the approach
    template<typename Derived>
    class BaseSpectrum {
    public:
        float operator()(float lambda) const {
            return static_cast<const Derived *>(this)->operator()(lambda);
        }

        [[nodiscard]] SampledSpectrum sample(const SampledWavelengths &lambda) const {
            return static_cast<const Derived *>(this)->sample(lambda);
        }

        [[nodiscard]] float maxValue() const {
            return static_cast<const Derived *>(this)->maxValue();
        }
    protected:
        // Prevents direct instantiation of the base class
        ~BaseSpectrum() = default;
    };


    //region General Spectral Distributions
    class ConstantSpectrum : public BaseSpectrum<ConstantSpectrum> {
    public:
        explicit ConstantSpectrum(float v) : v(v) {}

        float operator()(float lambda) const {
            return v;
        }

        [[nodiscard]] SampledSpectrum sample(const SampledWavelengths &lambda) const {
            return {};
        }

        [[nodiscard]] float maxValue() const { return v; }

    private:
        float v;
    };


    class DenselySampledSpectrum : public BaseSpectrum<DenselySampledSpectrum> {
    public:
        DenselySampledSpectrum(int lambdaMin, int lambdaMax) : lambdaMin(lambdaMin), lambdaMax(lambdaMax) {

        }
    private:
        int lambdaMin, lambdaMax;
    };
    //endregion

    //region Spectrum Wrapper
    enum class SpectrumType {
        Constant,
        DenselySampled
    };

    class Spectrum {
    public:

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