#pragma once

#include "JTX/Core/Primitive.h"
#include "JTX/Core/Lights.h"
#include "JTX/Core/Camera.h"
#include "JTX/Util/Util.h"

namespace JTX::Core {
        class Scene {
        public:
            using PrimitiveID = uint64_t;
            using LightID = uint64_t;

            explicit Scene(JTX::Core::Camera camera) : camera(camera) {};
            ~Scene() = default;

        private:
            std::unordered_map<PrimitiveID, JTX::Core::Primitive*> primitives;
            std::unordered_map<LightID, JTX::Core::DirLight*> lights;
            JTX::Core::Camera camera;

            JTX::Util::IDPool primitiveIDPool;
            JTX::Util::IDPool lightIDPool;
        };

}