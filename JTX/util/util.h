#pragma once

#include "JTX/util/vec3.h"
#include "JTX/util/mat4.h"
#include <queue>
#include <cmath>

namespace JTX::Util {
    inline float degToRad(float deg) { return deg * (M_PI / 180.0f); }

    class IDPool {
    public:
        IDPool() : nextID(0) {}
        ~IDPool() = default;

        [[nodiscard]] uint64_t getID() {
            if (pool.empty()) {return nextID++;}
            uint64_t id = pool.front();
            pool.pop();
            return id;
        }

        void releaseID(uint64_t id) { pool.push(id); }

    private:
        std::queue<uint64_t> pool;
        uint64_t nextID;
    };
}