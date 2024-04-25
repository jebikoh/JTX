#pragma once
#include "JTX/util/util.h"

namespace JTX::Core {
    class DirLight {
    public:
        explicit DirLight(JTX::Util::Vec3 direction) : direction(direction.normalize()) {}
        ~DirLight() = default;

        [[nodiscard]] const JTX::Util::Vec3& getDirection() const {
            return direction;
        }

        [[nodiscard]] float getIntensity(const JTX::Util::Vec3& normal) const {
            return std::max(0.0f, -normal.dot(direction));
        }

    private:
        JTX::Util::Vec3 direction;
    };
}


