#pragma once

#include "JTX/core/camera.hpp"
#include "JTX/core/lights.hpp"
#include "JTX/core/primitive.hpp"
#include "JTX/util/util.hpp"

namespace JTX::Core {
// Note to self: re-think out the design of primitive/light/camera ownership
class Scene {
public:
  using PrimitiveID = uint64_t;
  using LightID = uint64_t;

  explicit Scene(JTX::Core::Camera camera) : camera_(camera) {}
  ~Scene() = default;

  PrimitiveID addPrimitive(JTX::Core::Primitive &primitive) {
    PrimitiveID id = primitiveIDPool_.getID();
    primitives_[id] = &primitive;
    return id;
  }

  void removePrimitive(PrimitiveID id) {
    if (primitives_.find(id) != primitives_.end()) {
      primitives_.erase(id);
      primitiveIDPool_.releaseID(id);
    }
  }

  Primitive &getPrimitive(PrimitiveID id) {
    if (primitives_.find(id) != primitives_.end()) {
      return *primitives_[id];
    }
    throw std::runtime_error("Primitive with ID " + std::to_string(id) +
                             " not found");
  }

  [[nodiscard]] const Primitive &getPrimitive(PrimitiveID id) const {
    auto it = primitives_.find(id);
    if (it != primitives_.end()) {
      return *it->second;
    }
    throw std::runtime_error("Primitive with ID " + std::to_string(id) +
                             " not found");
  }

  LightID addLight(DirLight &light) {
    LightID id = lightIDPool_.getID();
    lights_[id] = &light;
    return id;
  }

  void removeLight(LightID id) {
    if (lights_.find(id) != lights_.end()) {
      lights_.erase(id);
      lightIDPool_.releaseID(id);
    }
  }

  DirLight &getLight(LightID id) {
    if (lights_.find(id) != lights_.end()) {
      return *lights_[id];
    }
    throw std::runtime_error("Light with ID " + std::to_string(id) +
                             " not found");
  }

  JTX::Core::Camera &getCamera() { return camera_; }

  std::unordered_map<PrimitiveID, JTX::Core::Primitive *> getPrimitives() {
    return this->primitives_;
  }

  int getNumPrimitives() { return (int)this->primitives_.size(); }
  int getNumLights() { return (int)this->lights_.size(); }

private:
  JTX::Core::Camera camera_;

  std::unordered_map<PrimitiveID, JTX::Core::Primitive *> primitives_;
  std::unordered_map<LightID, JTX::Core::DirLight *> lights_;

  JTX::Util::IDPool primitiveIDPool_;
  JTX::Util::IDPool lightIDPool_;
};
} // namespace JTX::Core