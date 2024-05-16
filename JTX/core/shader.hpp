#pragma once
#include "JTX/util/util.hpp"

namespace JTX::Core {
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void vertex(const float *vertex, const float *normal, float* out) = 0;
        virtual void fragment(const float *bary, const float *screen, const float *normal, float *color) = 0;
    };

    class DefaultShader : public Shader {
    public:
        struct Uniforms {
            JTX::Util::Mat4 cameraMatrix;
            JTX::Util::Vec3 lightDir;
        };

        void setUniforms(const Uniforms& uniforms) {
            this->uniforms_ = uniforms;
        }

        void vertex(const float *vertex, const float *normal, float* out) override;

        void fragment(const float *bary, const float *screen, const float *normal, float *color) override;

    private:
        Uniforms uniforms_;
    };
}
