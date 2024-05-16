#pragma once
#include "JTX/util/util.hpp"

namespace JTX::Core {
    struct UniformBuffer {
        JTX::Util::Mat4 cameraMatrix;
        JTX::Util::Vec3 lightDir;
        // Add as needed
    };

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void vertex(const float *vertex, const float *normal, float* out) = 0;
        virtual void fragment(const float *bary, const int *screen, const float *normal, float *color) = 0;
        virtual void bind(const UniformBuffer& ub) = 0;
    };

    class DefaultShader : public Shader {
    public:
        // TODO: passing the vertices as an array is pretty dangerous
        //       potential switch to passing Vec3/Vec4 in the future
        void vertex(const float *vertex, const float *normal, float* out) override;

        void fragment(const float *bary, const int *screen, const float *normal, float *color) override;

        void bind(const UniformBuffer& ub) override { this->ub_ = &ub; }

    private:
        const UniformBuffer *ub_;
    };
}
