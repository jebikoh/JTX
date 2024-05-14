#pragma once
#include "JTX/util/util.hpp"

namespace JTX::Core {
    class DirLight {
    public:
        explicit DirLight(JTX::Util::Vec3 direction) : direction_(direction.normalize()) {}
        ~DirLight() = default;

        [[nodiscard]] const JTX::Util::Vec3& getDirection() const {
            return direction_;
        }

        [[nodiscard]] float getIntensity(const JTX::Util::Vec3& normal) const {
            return std::max(0.0f, -normal.dot(direction_));
        }

    private:
        JTX::Util::Vec3 direction_;
    };
}


