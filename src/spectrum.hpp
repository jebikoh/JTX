#pragma once
#include <jtxlib/math/math.hpp>
#include <jtxlib/util/taggedptr.hpp>
#include <jtxlib/std/memory_resource.hpp>
#include <jtxlib/std/std.hpp>

namespace jtx {
    static constexpr float LAMBDA_MIN = 360.0f;
    static constexpr float LAMBDA_MAX = 830.0f;

    static constexpr int N_SPECTRUM_SAMPLES = 4;

    static constexpr float WEIN_DISPLACEMENT = 2.8977721e-3f;

    JTX_HOSTDEV
    float blackBody(const float lambda, const float temp) {
        if (temp <= 0) return 0;

        constexpr float c = 299792458.0f;
        constexpr float h = 6.62606957e-34f;
        constexpr float kb = 1.3806488e-23f;

        float l = lambda * 1e-9f;
        return (2 * h * c * c) / (jtx::pow(l, 5) * (fastExp((h * c) / (l * kb * temp)) - 1));
    }

    class SampledSpectrum {
    private:
        array<float, N_SPECTRUM_SAMPLES> data;
    public:
        JTX_HOSTDEV
        explicit SampledSpectrum(const float c) { ASSERT(!jtx::isNaN(c)); data.fill(c); }

        JTX_HOSTDEV
        explicit SampledSpectrum(const jtx::span<const float> v) {
            ASSERT(v.size() == N_SPECTRUM_SAMPLES);
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) {
                data[i] = v[i];
            }
        }

        SampledSpectrum() = default;

        JTX_HOSTDEV
        float operator[](const int i) const { return data[i]; }

        JTX_HOSTDEV
        float &operator[](const int i) { return data[i]; }

        JTX_HOSTDEV
        explicit operator bool() {
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) if (data[i] != 0) return true;
            return false;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator+=(const SampledSpectrum &other) {
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) data[i] += other[i];
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator+=(const float c) {
            ASSERT(!jtx::isNaN(c));
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) data[i] += c;
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator-=(const SampledSpectrum &other) {
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) data[i] -= other[i];
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator-=(const float c) {
            ASSERT(!jtx::isNaN(c));
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) data[i] -= c;
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator*=(const SampledSpectrum &other) {
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) data[i] *= other[i];
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator*=(const float c) {
            ASSERT(!jtx::isNaN(c));
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) data[i] *= c;
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator/=(const SampledSpectrum &other) {
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) {
                ASSERT(other[i] != 0);
                data[i] /= other[i];
            }
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum &operator/=(const float c) {
            ASSERT(c != 0);
            ASSERT(!jtx::isNaN(c));
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) data[i] /= c;
            return *this;
        }

        JTX_HOSTDEV
        SampledSpectrum operator+(const SampledSpectrum &other) const {
            SampledSpectrum result = *this;
            return result += other;
        }

        JTX_HOSTDEV
        SampledSpectrum operator+(const float c) const {
            SampledSpectrum result = *this;
            return result += c;
        }

        JTX_HOSTDEV
        friend SampledSpectrum operator+(const float c, const SampledSpectrum &s) {
            return s + c;
        }

        JTX_HOSTDEV
        SampledSpectrum operator-(const SampledSpectrum &other) const {
            SampledSpectrum result = *this;
            return result -= other;
        }

        JTX_HOSTDEV
        SampledSpectrum operator-(const float c) const {
            SampledSpectrum result = *this;
            return result -= c;
        }

        JTX_HOSTDEV
        friend SampledSpectrum operator-(const float c, const SampledSpectrum &s) {
            return s - c;
        }

        JTX_HOSTDEV
        SampledSpectrum operator*(const SampledSpectrum &other) const {
            SampledSpectrum result = *this;
            return result *= other;
        }

        JTX_HOSTDEV
        SampledSpectrum operator*(const float c) const {
            SampledSpectrum result = *this;
            return result *= c;
        }

        JTX_HOSTDEV
        friend SampledSpectrum operator*(const float c, const SampledSpectrum &s) {
            return s * c;
        }

        JTX_HOSTDEV
        SampledSpectrum operator/(const SampledSpectrum &other) const {
            SampledSpectrum result = *this;
            return result /= other;
        }

        JTX_HOSTDEV
        SampledSpectrum operator/(const float c) const {
            SampledSpectrum result = *this;
            return result /= c;
        }

        JTX_HOSTDEV
        bool operator==(const SampledSpectrum &other) const { return data == other.data; }

        JTX_HOSTDEV
        bool operator!=(const SampledSpectrum &other) const { return data != other.data; }

        [[nodiscard]]
        JTX_HOSTDEV
        float minValue() const {
            float result = data[0];
            for (int i = 1; i < N_SPECTRUM_SAMPLES; ++i) result = min(result, data[i]);
            return result;
        }

        [[nodiscard]]
        JTX_HOSTDEV
        float maxValue() const {
            float result = data[0];
            for (int i = 1; i < N_SPECTRUM_SAMPLES; ++i) result = max(result, data[i]);
            return result;
        }

        [[nodiscard]]
        JTX_HOSTDEV
        float average() const {
            float result = 0.0f;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result += data[i];
            return result / N_SPECTRUM_SAMPLES;
        }

        JTX_HOSTDEV
        static SampledSpectrum safeDiv(const SampledSpectrum &a, const SampledSpectrum &b) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) {
                if (b[i] != 0) result[i] = a[i] / b[i];
                else result[i] = 0.0f;
            }
            return result;
        }

        JTX_HOSTDEV
        static SampledSpectrum lerp(const SampledSpectrum &a, const SampledSpectrum &b, const float t) {
            return (1 - t) * a + b * t;
        }

        JTX_HOSTDEV
        static SampledSpectrum sqrt(const SampledSpectrum &s) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result[i] = jtx::sqrt(s[i]);
            return result;
        }

        JTX_HOSTDEV
        static SampledSpectrum safeSqrt(const SampledSpectrum &s) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result[i] = jtx::safeSqrt(s[i]);
            return result;
        }

        JTX_HOSTDEV
        static SampledSpectrum pow(const SampledSpectrum &s, const float n) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result[i] = jtx::pow(s[i], n);
            return result;
        }

        JTX_HOSTDEV
        static SampledSpectrum exp(const SampledSpectrum &s) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result[i] = jtx::exp(s[i]);
            return result;
        }

        JTX_HOSTDEV
        static SampledSpectrum fastExp(const SampledSpectrum &s) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result[i] = jtx::fastExp(s[i]);
            return result;
        }

        JTX_HOSTDEV
        static SampledSpectrum clamp(const SampledSpectrum &s, const float lo, const float hi) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result[i] = jtx::clamp(s[i], lo, hi);
            return result;
        }

        JTX_HOSTDEV
        static SampledSpectrum clampZero(const SampledSpectrum &s) {
            SampledSpectrum result;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) result[i] = jtx::clampZero(s[i]);
            return result;
        }

        JTX_HOSTDEV
        static float minValue(const SampledSpectrum &s) { return s.minValue(); }

        JTX_HOSTDEV
        static float maxValue(const SampledSpectrum &s) { return s.maxValue(); }

        JTX_HOSTDEV
        static float average(const SampledSpectrum &s) { return s.average(); }
    };

    class SampledWavelengths {
        array<float, N_SPECTRUM_SAMPLES> lambda, pdf;
    public:
        static SampledWavelengths sampleUniform(const float u, const float lMin = LAMBDA_MIN, const float lMax = LAMBDA_MAX) {
            SampledWavelengths r;
            r.lambda[0] = lerp(lMin, lMax, u);
            r.pdf[0] = 1 / (lMax - lMin);

            const float delta = (lMax - lMin) / N_SPECTRUM_SAMPLES;
            for (int i = 1; i < N_SPECTRUM_SAMPLES; ++i) {
                r.lambda[i] = r.lambda[i-1] + delta;
                if (r.lambda[i] > lMax) r.lambda[i] = r.lambda[i] - lMax + lMin;
                r.pdf[i] = r.pdf[0];
            }
            return r;
        }

        float operator[](const int i) const { return lambda[i]; }
        float &operator[](const int i) { return lambda[i]; }

        [[nodiscard]]
        SampledSpectrum PDF() const { return SampledSpectrum(pdf); }

        // Usually terminates early
        [[nodiscard]]
        bool secondTerminated() const {
            for (int i = 1; i < N_SPECTRUM_SAMPLES; ++i) {
                if (pdf[i] != 0) return false;
            }
            return true;
        }

        void terminateSecondary() {
            if (secondTerminated()) return;
            for (int i = 1; i < N_SPECTRUM_SAMPLES; ++i) pdf[i] = 0;
            pdf[0] /= N_SPECTRUM_SAMPLES;
        }
    };

    class ConstantSpectrum;
    class DenselySampledSpectrum;
    class PiecewiseLinearSpectrum;

    class Spectrum : public TaggedPtr<ConstantSpectrum, DenselySampledSpectrum, PiecewiseLinearSpectrum> {
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
        SampledSpectrum Sample(const SampledWavelengths &lambda) const {
            return SampledSpectrum(c);
        }

        [[nodiscard]]
        JTX_HOSTDEV
        float maxValue() const { return c; }
    private:
        float c;
    };

    class DenselySampledSpectrum {
        int lambdaMin, lambdaMax;
        vector<float> values;
    public:
        JTX_HOST
        explicit DenselySampledSpectrum(const int lambdaMin = LAMBDA_MIN, const int lambdaMax = LAMBDA_MAX, const Allocator alloc = {}):
            lambdaMin(lambdaMin),
            lambdaMax(lambdaMax),
            values(lambdaMax - lambdaMin + 1, alloc)
        {}

        JTX_HOST
        DenselySampledSpectrum(const Spectrum &s, const Allocator alloc) : DenselySampledSpectrum(s, lambdaMin, lambdaMax, alloc) {};

        JTX_HOST
        explicit DenselySampledSpectrum(const Spectrum& s, const int lambdaMin = LAMBDA_MIN, const int lambdaMax = LAMBDA_MAX, const Allocator alloc = {}) :
            lambdaMin(lambdaMin),
            lambdaMax(lambdaMax),
            values(lambdaMax - lambdaMin + 1, alloc)
        {
            if (s) for (int lambda = lambdaMin; lambda <= lambdaMax; ++lambda) values[lambda - lambdaMin] = s(lambda);
        }

        JTX_HOST
        DenselySampledSpectrum(const DenselySampledSpectrum &s, const Allocator alloc) :
            lambdaMin(s.lambdaMin),
            lambdaMax(s.lambdaMax),
            values(s.values.begin(), s.values.end(), alloc)
        {}

        [[nodiscard]]
        JTX_HOSTDEV
        SampledSpectrum sample(const SampledWavelengths &lambda) const {
            SampledSpectrum s;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) {
                int offset = jtx::lround(lambda[i]) - lambdaMin;
                if (offset < 0 || offset >= values.size()) s[i] = 0;
                else s[i] = values[offset];
            }
            return s;
        }

        JTX_HOSTDEV
        void scale(const float s) { // NOLINT(*-convert-member-functions-to-static)
            for (float v& : values) v *= s;
        }

        JTX_HOSTDEV
        [[nodiscard]]
        float maxValue() const { return *max_element(values.begin(), values.end()); }

        JTX_HOSTDEV
        float operator()(const float lambda) const {
            const int offset = jtx::lround(lambda) - lambdaMin;
            if (offset < 0 || offset >= values.size()) return 0;
            return values[offset];
        }

        JTX_HOSTDEV
        bool operator==(const DenselySampledSpectrum &s) const {
            if (lambdaMin != s.lambdaMin || lambdaMax != s.lambdaMax || values.size() != s.values.size()) return false;
            for (auto i = 0; i < values.size(); ++i) if (values[i] != s.values[i]) return false;
            return true;
        }
    };

    class PiecewiseLinearSpectrum {
        vector<float> lambdas, values;
    public:
        JTX_HOST
        PiecewiseLinearSpectrum(const span<const float> lambda, const span<const float> values, const Allocator alloc = {}) :
            lambdas(lambda.begin(), lambda.end(), alloc),
            values(values.begin(), values.end(), alloc)
        {
            ASSERT(lambda.size() == values.size());
            for (int i = 0; i < lambda.size() - 1; ++i) ASSERT(lambda[i] < lambda[i + 1]);
        }

        JTX_HOST
        PiecewiseLinearSpectrum() = default;

        JTX_HOSTDEV
        void scale(const float s) {
            for (float v& : values) v *= s;
        }

        JTX_HOSTDEV
        [[nodiscard]]
        float maxValue() const {
            if (values.empty()) return 0;
            return *max_element(values.begin(), values.end());
        }

        JTX_HOSTDEV
        float operator()(const float lambda) const {
            if (lambdas.empty() || lambda < lambdas.front() || lambda > lambdas.back()) return 0;
            const int o = findInterval(lambdas.size(), [&](const int i) { return lambdas[i] <= lambda; });
            return lerp(values[o], values[o + 1], (lambda - lambdas[o]) / (lambdas[o + 1] - lambdas[o]));
        }

        JTX_HOSTDEV
        SampledSpectrum sample(const SampledWavelengths &lambda) const {
            SampledSpectrum s;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) s[i] = (*this)(lambda[i]);
            return s;
        }
    };

    class BlackbodySpectrum {
        float t;
        float normFactor;
    public:
        JTX_HOSTDEV
        explicit BlackbodySpectrum(float t) : t(t) {
            normFactor = 1 / jtx::blackBody((WEIN_DISPLACEMENT / t) * 1e9f, t);
        }

        JTX_HOSTDEV
        float operator()(int lambda) const {
            return blackBody(lambda, t) * normFactor;
        }


        JTX_HOSTDEV
        [[nodiscard]]
        SampledSpectrum sample(const SampledWavelengths &lambda) const {
            SampledSpectrum s;
            for (int i = 0; i < N_SPECTRUM_SAMPLES; ++i) s[i] = blackBody(lambda[i], t) * normFactor;
            return s;
        }

        JTX_HOSTDEV
        [[nodiscard]]
        float maxValue() const { return 1.0f; } // NOLINT(*-convert-member-functions-to-static)
    };

    JTX_HOSTDEV
    float innerProduct(const Spectrum &f, const Spectrum &g) {
        float integral = 0;
        for (float lambda = LAMBDA_MIN; lambda <= LAMBDA_MAX; ++lambda) {
            integral += f(lambda) * g(lambda);
        }
        return integral;
    }

    namespace spectra {
    inline const DenselySampledSpectrum &X();
    inline const DenselySampledSpectrum &Y();
    inline const DenselySampledSpectrum &Z();
    }
}