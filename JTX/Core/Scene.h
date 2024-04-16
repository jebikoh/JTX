#pragma once

#include "JTX/Core/Primitive.h"
#include "JTX/Core/Lights.h"
#include "JTX/Core/Camera.h"
#include "JTX/Util/Util.h"

namespace JTX::Core {
    // Note to self: re-think out the design of primitive/light/camera ownership
    class Scene {
    public:
        using PrimitiveID = uint64_t;
        using LightID = uint64_t;

        explicit Scene(JTX::Core::Camera camera) : camera(camera) {}
        ~Scene() = default;


        PrimitiveID addPrimitive(JTX::Core::Primitive &primitive) {
            PrimitiveID id = primitiveIDPool.getID();
            primitives[id] = &primitive;
            return id;
        }

        void removePrimitive(PrimitiveID id) {
            if (primitives.find(id) != primitives.end()) {
                primitives.erase(id);
                primitiveIDPool.releaseID(id);
            }
        }

        Primitive &getPrimitive(PrimitiveID id) {
            if (primitives.find(id) != primitives.end()) {
                return *primitives[id];
            }
            throw std::runtime_error("Primitive with ID " + std::to_string(id) + " not found");
        }

        LightID addLight(DirLight &light) {
            LightID id = lightIDPool.getID();
            lights[id] = &light;
            return id;
        }

        void removeLight(LightID id) {
            if (lights.find(id) != lights.end()) {
                lights.erase(id);
                lightIDPool.releaseID(id);
            }
        }

        DirLight &getLight(LightID id) {
            if (lights.find(id) != lights.end()) {
                return *lights[id];
            }
            throw std::runtime_error("Light with ID " + std::to_string(id) + " not found");
        }

        JTX::Core::Camera &getCamera() { return camera; }

        std::unordered_map<PrimitiveID, JTX::Core::Primitive*> getPrimitives() { return this->primitives; }

        int getNumPrimitives() { return (int)this->primitives.size(); }
        int getNumLights() { return (int)this->lights.size(); }


    private:
        JTX::Core::Camera camera;

        std::unordered_map<PrimitiveID, JTX::Core::Primitive*> primitives;
        std::unordered_map<LightID, JTX::Core::DirLight*> lights;

        JTX::Util::IDPool primitiveIDPool;
        JTX::Util::IDPool lightIDPool;
    };
}