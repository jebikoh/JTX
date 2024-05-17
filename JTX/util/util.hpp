#pragma once

#include "JTX/util/vec3.hpp"
#include "JTX/util/vec4.hpp"
#include "JTX/util/mat4.hpp"
#include "JTX/util/color.hpp"
#include <queue>
#include <cmath>

namespace JTX::Util {
    static inline float degToRad(float deg) { return deg * (M_PI / 180.0f); }

    class IDPool {
    public:
        IDPool() : nextID_(0) {}
        ~IDPool() = default;

        [[nodiscard]] uint64_t getID() {
            if (pool_.empty()) {return nextID_++;}
            uint64_t id = pool_.front();
            pool_.pop();
            return id;
        }

        void releaseID(uint64_t id) { pool_.push(id); }

    private:
        std::queue<uint64_t> pool_;
        uint64_t nextID_;
    };

    /**
     * I think this method is pretty dangerous as it assumes that the input vector is of size 4
     * I can't think of a better solution at the moment
     *
     * TODO: Profile this. BLAS might take longer than an unrolled loop here since M is only 4x4
     */
    static void applyTransform(const Mat4* tf, const float *v, float *out) {
        cblas_sgemv(CblasRowMajor, CblasNoTrans, 4, 4, 1.0f,
                    reinterpret_cast<const float*>(tf->data), 4, v, 1, 0.0f, out, 1);
    }
}