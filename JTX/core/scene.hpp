#pragma once

#include "JTX/core/camera.hpp"
#include "JTX/core/lights.hpp"
#include "JTX/core/primitive.hpp"
#include "JTX/util/util.hpp"

namespace JTX::Core {
class Scene {
public:
  using PrimitiveID = uint64_t;
  using LightID = uint64_t;

  explicit Scene(JTX::Core::Camera camera) : camera_(camera) {}
  ~Scene() = default;

  PrimitiveID addPrimitive(std::unique_ptr<JTX::Core::Primitive> primitive) {
    PrimitiveID id = primitiveIDPool_.getID();
    size_t index = primitives_.size();
    primitivesMap_[id] = index;
    primitives_.push_back(std::move(primitive));
    return id;
  }

  void removePrimitive(PrimitiveID id) {
    auto it = primitivesMap_.find(id);
    if (it != primitivesMap_.end()) {
      size_t index = it->second;
      primitives_.erase(primitives_.begin() + index);
      primitivesMap_.erase(it);
      primitiveIDPool_.releaseID(id);

      // Adjust indices of subsequent primitives
      for (auto &pair : primitivesMap_) {
        if (pair.second > index) {
          pair.second--;
        }
      }
    }
  }

  Primitive &getPrimitive(PrimitiveID id) {
    auto it = primitivesMap_.find(id);
    if (it != primitivesMap_.end()) {
      return *primitives_[it->second];
    }
    throw std::runtime_error("Primitive with ID " + std::to_string(id) +
                             " not found");
  }

  [[nodiscard]] const Primitive &getPrimitive(PrimitiveID id) const {
    auto it = primitivesMap_.find(id);
    if (it != primitivesMap_.end()) {
      return *primitives_[it->second];
    }
    throw std::runtime_error("Primitive with ID " + std::to_string(id) +
                             " not found");
  }

  LightID addLight(std::unique_ptr<DirLight> light) {
    LightID id = lightIDPool_.getID();
    size_t index = lights_.size();
    lightsMap_[id] = index;
    lights_.push_back(std::move(light));
    return id;
  }

  void removeLight(LightID id) {
    auto it = lightsMap_.find(id);
    if (it != lightsMap_.end()) {
      size_t index = it->second;
      lights_.erase(lights_.begin() + index);
      lightsMap_.erase(it);
      lightIDPool_.releaseID(id);

      // Adjust indices of subsequent lights
      for (auto &pair : lightsMap_) {
        if (pair.second > index) {
          pair.second--;
        }
      }
    }
  }

  DirLight &getLight(LightID id) {
    auto it = lightsMap_.find(id);
    if (it != lightsMap_.end()) {
      return *lights_[it->second];
    }
    throw std::runtime_error("Light with ID " + std::to_string(id) +
                             " not found");
  }

  [[nodiscard]] const DirLight &getLight(LightID id) const {
    auto it = lightsMap_.find(id);
    if (it != lightsMap_.end()) {
      return *lights_[it->second];
    }
    throw std::runtime_error("Light with ID " + std::to_string(id) +
                             " not found");
  }

  JTX::Core::Camera &getCamera() { return camera_; }

  [[nodiscard]] const std::vector<std::unique_ptr<JTX::Core::Primitive>> &
  getPrimitives() const {
    return primitives_;
  }

  [[nodiscard]] int getNumPrimitives() const {
    return static_cast<int>(primitives_.size());
  }
  [[nodiscard]] int getNumLights() const {
    return static_cast<int>(lights_.size());
  }

private:
  JTX::Core::Camera camera_;

  std::vector<std::unique_ptr<JTX::Core::Primitive>> primitives_;
  std::vector<std::unique_ptr<JTX::Core::DirLight>> lights_;

  std::unordered_map<PrimitiveID, size_t> primitivesMap_;
  std::unordered_map<LightID, size_t> lightsMap_;

  JTX::Util::IDPool primitiveIDPool_;
  JTX::Util::IDPool lightIDPool_;
};
} // namespace JTX::Core