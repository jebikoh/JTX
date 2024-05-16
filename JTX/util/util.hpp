#pragma once

#include "JTX/util/vec3.hpp"
#include "JTX/util/vec4.hpp"
#include "JTX/util/mat4.hpp"
#include "JTX/util/color.hpp"
#include <queue>
#include <cmath>

namespace JTX::Util {
    inline float degToRad(float deg) { return deg * (M_PI / 180.0f); }

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
}