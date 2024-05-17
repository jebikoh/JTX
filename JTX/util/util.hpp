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
     * Applies an affine transformation to a 4D vector in-place
     * @param tf 4x4 affine transformation (Mat4)
     * @param v 4D vector to transform. If the array is not of size 4, the behavior is undefined
     *
     * NOTE: this method is not safe and does not check for the size of the array
     */
    static void applyTransform(const Mat4 &tf, float *v) {
        float x = v[0] * tf[0][0] + v[1] * tf[1][0] + v[2] * tf[2][0] + v[3] * tf[3][0];
        float y = v[0] * tf[0][1] + v[1] * tf[1][1] + v[2] * tf[2][1] + v[3] * tf[3][1];
        float z = v[0] * tf[0][2] + v[1] * tf[1][2] + v[2] * tf[2][2] + v[3] * tf[3][2];
        float w = v[0] * tf[0][3] + v[1] * tf[1][3] + v[2] * tf[2][3] + v[3] * tf[3][3];

        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
}