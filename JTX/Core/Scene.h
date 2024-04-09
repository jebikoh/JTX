#pragma once

#include "JTX/Core/Primitive.h"
#include "JTX/Core/Lights.h"

namespace JTX::Core {
        class Scene {
        public:
            Scene() = default;
            ~Scene() = default;



        private:
            std::vector<Primitive> primitives;
            std::vector<DirLight> lights;
        };

}