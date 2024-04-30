#pragma once
#include "JTX/util/util.h"

namespace JTX::Core {
    typedef enum {
        PERSPECTIVE,
        ORTHOGRAPHIC
    } ProjectionType;

    class Camera {
    public:
        Camera(JTX::Util::Vec3 pos, JTX::Util::Vec3 target, JTX::Util::Vec3 up, float fov, float near, float far) {
            this->pos = pos;
            this->lookAt = target - pos;
            this->lookAt.normalize();
            this->up = up.normalize();
            this->fov = fov;
            this->near = near;
            this->far = far;
            this->t = JTX::Util::Mat4();
            this->dirty = true;
        }
        ~Camera() = default;

        [[nodiscard]] JTX::Util::Mat4 getViewMatrix() const {
            JTX::Util::Vec3 right = this->lookAt.cross(this->up).normalize();
            JTX::Util::Vec3 vup = right.cross(this->lookAt);

            return {
                right.x, right.y, right.z, -right.dot(this->pos),
                vup.x, vup.y, vup.z, -vup.dot(this->pos),
                -this->lookAt.x, -this->lookAt.y, -this->lookAt.z, this->lookAt.dot(this->pos),
                0, 0, 0, 1
            };
        }

        [[nodiscard]] JTX::Util::Mat4 getProjMatrix(const float aspectRatio, ProjectionType projType) const {
            if (projType == PERSPECTIVE) {
                float f = 1 / std::tan(this->fov / 2);
                return {
                    f / aspectRatio, 0, 0, 0,
                    0, f, 0, 0,
                    0, 0, (this->far + this->near) / (this->far - this->near), (2 * this->far * this->near) / (this->far - this->near),
                    0, 0, -1, 0
                };
            } else {
                return {};
            }
        }

        [[nodiscard]] JTX::Util::Mat4 getCameraMatrix(const float aspectRatio, ProjectionType projectionType) {
            if (!this->dirty) { return this->t; }

            this->t = JTX::Util::Mat4::matmul(this->getProjMatrix(aspectRatio, projectionType), this->getViewMatrix());
            this->dirty = false;
            return this->t;
        }

        [[nodiscard]] JTX::Util::Vec3 getPos() const { return this->pos; }
        [[nodiscard]] JTX::Util::Vec3 getLookAt() const { return this->lookAt; }
        [[nodiscard]] JTX::Util::Vec3 getUp() const { return this->up; }
        [[nodiscard]] float getFov() const { return this->fov; }
        [[nodiscard]] float getNear() const { return this->near; }
        [[nodiscard]] float getFar() const { return this->far; }

        void setPos(JTX::Util::Vec3 npos) {
            this->pos = npos;
            this->dirty = true;
        }

        void setLookAt(JTX::Util::Vec3 target) {
            this->lookAt = target - this->pos;
            this->lookAt.normalize();
            this->dirty = true;
        }

        void setUp(JTX::Util::Vec3 nup) {
            this->up = nup.normalize();
            this->dirty = true;
        }

        void setFov(float nfov) {
            this->fov = nfov;
            this->dirty = true;
        }

        void setNear(float nnear) {
            this->near = nnear;
            this->dirty = true;
        }

        void setFar(float nfar) {
            this->far = nfar;
            this->dirty = true;
        }

    private:
        JTX::Util::Vec3 pos;
        JTX::Util::Vec3 lookAt;
        JTX::Util::Vec3 up;
        float fov;
        float near;
        float far;
        JTX::Util::Mat4 t;
        bool dirty;
    };
}