#pragma once
#include "JTX/util/util.hpp"

namespace JTX::Core {
typedef enum { PERSPECTIVE, ORTHOGRAPHIC } ProjectionType;

/**
 * @brief Camera class
 * Stores camera's transformation matrix and other properties.
 *
 * Cache's the cameras transformation matrix on calculation. If camera hasn't
 * been updated since the last call, the cached matrix is returned. All setters
 * will cause the matrix to be recalculated on the next call.
 */
class Camera {
public:
  /**
   * @brief Constructs a new Camera object
   * @param pos Camera's position
   * @param target The point the camera is looking at
   * @param up Up vector
   * @param fov Field of view in radians
   * @param near Near plane
   * @param far Far plane
   */
  Camera(JTX::Util::Vec3f pos, JTX::Util::Vec3f target, JTX::Util::Vec3f up,
         float fov, float near, float far) {
    this->pos_ = pos;
    this->lookAt_ = target - pos;
    this->lookAt_.normalize();
    this->up_ = up.normalize();
    this->fov_ = fov;
    this->near_ = near;
    this->far_ = far;
    this->t_ = JTX::Util::Mat4();
    this->dirty_ = true;
  }
  ~Camera() = default;

  /**
   * @brief Returns the view matrix
   * @return JTX::Util::Mat4 View matrix
   */
  [[nodiscard]] JTX::Util::Mat4 getViewMatrix() const {
    JTX::Util::Vec3f right = this->lookAt_.cross(this->up_).normalize();
    JTX::Util::Vec3f vup = right.cross(this->lookAt_);

    return {right.x,
            right.y,
            right.z,
            -right.dot(this->pos_),
            vup.x,
            vup.y,
            vup.z,
            -vup.dot(this->pos_),
            -this->lookAt_.x,
            -this->lookAt_.y,
            -this->lookAt_.z,
            this->lookAt_.dot(this->pos_),
            0,
            0,
            0,
            1};
  }

  /**
   * @brief Returns the projection matrix
   * @param aspectRatio Aspect ratio of the screen (h/w)
   * @param projType Type of projection (only PERSPECTIVE is supported)
   * @return JTX::Util::Mat4 Projection matrix
   */
  [[nodiscard]] JTX::Util::Mat4 getProjMatrix(const float aspectRatio,
                                              ProjectionType projType) const {
    if (projType == PERSPECTIVE) {
      float f = 1 / std::tan(this->fov_ / 2);
      return {f / aspectRatio,
              0,
              0,
              0,
              0,
              f,
              0,
              0,
              0,
              0,
              (this->far_ + this->near_) / (this->far_ - this->near_),
              (2 * this->far_ * this->near_) / (this->far_ - this->near_),
              0,
              0,
              -1,
              0};
    } else {
      return {};
    }
  }

  /**
   * @brief Returns the camera matrix.
   *
   * Returns the camera matrix. If the camera has not been updated since the
   * last call, the cached matrix is returned. Otherwise, the matrix is
   * recalculated and cached.
   *
   * @param aspectRatio
   * @param projectionType
   * @return
   */
  [[nodiscard]] JTX::Util::Mat4 getCameraMatrix(const float aspectRatio,
                                                ProjectionType projectionType) {
    if (!this->dirty_) {
      return this->t_;
    }

    this->t_ = JTX::Util::Mat4::matmul(
        this->getProjMatrix(aspectRatio, projectionType),
        this->getViewMatrix());
    this->dirty_ = false;
    return this->t_;
  }

  [[nodiscard]] JTX::Util::Vec3f getPos() const { return this->pos_; }
  [[nodiscard]] JTX::Util::Vec3f getLookAt() const { return this->lookAt_; }
  [[nodiscard]] JTX::Util::Vec3f getUp() const { return this->up_; }
  [[nodiscard]] float getFov() const { return this->fov_; }
  [[nodiscard]] float getNear() const { return this->near_; }
  [[nodiscard]] float getFar() const { return this->far_; }

  void setPos(JTX::Util::Vec3f npos) {
    this->pos_ = npos;
    this->dirty_ = true;
  }

  void setLookAt(JTX::Util::Vec3f target) {
    this->lookAt_ = target - this->pos_;
    this->lookAt_.normalize();
    this->dirty_ = true;
  }

  void setUp(JTX::Util::Vec3f nup) {
    this->up_ = nup.normalize();
    this->dirty_ = true;
  }

  void setFov(float nfov) {
    this->fov_ = nfov;
    this->dirty_ = true;
  }

  void setNear(float nnear) {
    this->near_ = nnear;
    this->dirty_ = true;
  }

  void setFar(float nfar) {
    this->far_ = nfar;
    this->dirty_ = true;
  }

private:
  JTX::Util::Vec3f pos_;
  JTX::Util::Vec3f lookAt_;
  JTX::Util::Vec3f up_;
  float fov_;
  float near_;
  float far_;
  JTX::Util::Mat4 t_;
  bool dirty_;
};
} // namespace JTX::Core