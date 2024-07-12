#pragma once

#include <jtxlib/math/mat4.hpp>
#include <jtxlib/math/vec3.hpp>
#include <jtxlib/math/vecmath.hpp>


namespace jtx {
    class Transform {
    public:
        //region Constructors
        Transform() : m(Mat4(1.0f)), mInv(Mat4(1.0f)) {};

        Transform(const Mat4 &m, const Mat4 &mInv) : m(m), mInv(mInv) {};

        explicit Transform(const Mat4 &m) : m(m) {
            std::optional<Mat4> inv = m.inverse();
            if (inv.has_value()) {
                mInv = inv.value();
            } else {
                float nan = std::numeric_limits<float>::signaling_NaN();
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        mInv[i][j] = nan;
                    }
                }
            }
        }

        explicit Transform(const float mat[4][4]) : Transform(Mat4(mat)) {};

        ~Transform() = default;
        //endregion

        //region Getters
        [[nodiscard]] const Mat4 &getMatrix() const {
            return m;
        }

        [[nodiscard]] const Mat4 &getInverseMatrix() const {
            return mInv;
        }
        //endregion

        //region Operators
        bool operator==(const Transform &other) const {
            return m == other.m;
        }

        bool operator!=(const Transform &other) const {
            return m != other.m;
        }
        //endregion

        //region Methods
        [[nodiscard]] bool isIdentity() const { return m.isIdentity(); }

        [[nodiscard]] inline Transform inverse() const {
            return {mInv, m};
        }

        [[nodiscard]] inline Transform transpose() const {
            return {m.transpose(), mInv.transpose()};

        }

        // Need to differentiate because points and normals are just typedefs

        JTX_NUM_ONLY_T
        inline Point3<T> applyToPoint(const Point3<T> &p) const {
            T xp = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3];
            T yp = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3];
            T zp = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3];
            T wp = m[3][0] * p.x + m[3][1] * p.y + m[3][2] * p.z + m[3][3];

            if (wp == 1) {
                return {xp, yp, zp};
            } else {
                return Point3f(xp, yp, zp) / wp;
            }
        }

        JTX_NUM_ONLY_T
        inline Point3<T> applyInverseToPoint(const Point3<T> &p) const {
            T xp = mInv[0][0] * p.x + mInv[0][1] * p.y + mInv[0][2] * p.z + mInv[0][3];
            T yp = mInv[1][0] * p.x + mInv[1][1] * p.y + mInv[1][2] * p.z + mInv[1][3];
            T zp = mInv[2][0] * p.x + mInv[2][1] * p.y + mInv[2][2] * p.z + mInv[2][3];
            T wp = mInv[3][0] * p.x + mInv[3][1] * p.y + mInv[3][2] * p.z + mInv[3][3];

            if (wp == 1) {
                return {xp, yp, zp};
            } else {
                return Point3f(xp, yp, zp) / wp;
            }
        }

        JTX_NUM_ONLY_T
        inline Vec3<T> applyToVec(const Vec3<T> &v) const {
            return {m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
                    m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
                    m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z};
        }

        JTX_NUM_ONLY_T
        inline Vec3<T> applyInverseToVec(const Vec3<T> &v) const {
            return {mInv[0][0] * v.x + mInv[0][1] * v.y + mInv[0][2] * v.z,
                    mInv[1][0] * v.x + mInv[1][1] * v.y + mInv[1][2] * v.z,
                    mInv[2][0] * v.x + mInv[2][1] * v.y + mInv[2][2] * v.z};
        }

        [[nodiscard]] inline Normal3f applyToNormal(const Normal3f &n) const {
            return {mInv[0][0] * n.x + mInv[1][0] * n.y + mInv[2][0] * n.z,
                    mInv[0][1] * n.x + mInv[1][1] * n.y + mInv[2][1] * n.z,
                    mInv[0][2] * n.x + mInv[1][2] * n.y + mInv[2][2] * n.z};
        }

        [[nodiscard]] inline Normal3f applyInverseToNormal(const Normal3f &n) const {
            return {m[0][0] * n.x + m[1][0] * n.y + m[2][0] * n.z,
                    m[0][1] * n.x + m[1][1] * n.y + m[2][1] * n.z,
                    m[0][2] * n.x + m[1][2] * n.y + m[2][2] * n.z};
        }


        //endregion

        //region Static methods
        static Transform translate(const float delta) {
            Mat4 m(1, 0, 0, delta,
                   0, 1, 0, delta,
                   0, 0, 1, delta,
                   0, 0, 0, 1);
            Mat4 mInv(1, 0, 0, -delta,
                      0, 1, 0, -delta,
                      0, 0, 1, -delta,
                      0, 0, 0, 1);
            return {m, mInv};
        }

        static Transform translate(const Vec3f &v) {
            Mat4 m(1, 0, 0, v.x,
                   0, 1, 0, v.y,
                   0, 0, 1, v.z,
                   0, 0, 0, 1);
            Mat4 mInv(1, 0, 0, -v.x,
                      0, 1, 0, -v.y,
                      0, 0, 1, -v.z,
                      0, 0, 0, 1);
            return {m, mInv};
        }

        static Transform scale(float sx, float sy, float sz) {
            ASSERT(sx != 0 && sy != 0 && sz != 0);
            Mat4 m(sx, 0, 0, 0,
                   0, sy, 0, 0,
                   0, 0, sz, 0,
                   0, 0, 0, 1);
            Mat4 mInv(1 / sx, 0, 0, 0,
                      0, 1 / sy, 0, 0,
                      0, 0, 1 / sz, 0,
                      0, 0, 0, 1);
            return {m, mInv};
        }

        static Transform rotateX(float theta) {
            float sinTheta = std::sin(jtx::radians(theta));
            float cosTheta = std::cos(jtx::radians(theta));
            Mat4 m(1, 0, 0, 0,
                   0, cosTheta, -sinTheta, 0,
                   0, sinTheta, cosTheta, 0,
                   0, 0, 0, 1);
            return {m, m.transpose()};
        }

        static Transform rotateY(float theta) {
            float sinTheta = std::sin(jtx::radians(theta));
            float cosTheta = std::cos(jtx::radians(theta));
            Mat4 m(cosTheta, 0, sinTheta, 0,
                   0, 1, 0, 0,
                   -sinTheta, 0, cosTheta, 0,
                   0, 0, 0, 1);
            return {m, m.transpose()};
        }

        static Transform rotateZ(float theta) {
            float sinTheta = std::sin(jtx::radians(theta));
            float cosTheta = std::cos(jtx::radians(theta));
            Mat4 m(cosTheta, -sinTheta, 0, 0,
                   sinTheta, cosTheta, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1);
            return {m, m.transpose()};
        }

        static Transform rotate(float sinTheta, float cosTheta, const Vec3f& axis) {
            Vec3f a = jtx::normalize(axis);
            Mat4 m;
            // Compute rotation of first basis vector
            m[0][0] = a.x * a.x + (1 - a.x * a.x) * cosTheta;
            m[0][1] = a.x * a.y * (1 - cosTheta) - a.z * sinTheta;
            m[0][2] = a.x * a.z * (1 - cosTheta) + a.y * sinTheta;
            m[0][3] = 0;
            // Compute rotation of the second basis vector
            m[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
            m[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
            m[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
            m[1][3] = 0;

            m[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
            m[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
            m[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
            m[2][3] = 0;

            m[3][0] = 0;
            m[3][1] = 0;
            m[3][2] = 0;
            m[3][3] = 1;

            return {m, m.transpose()};
        }

        static Transform rotate(float theta, const Vec3f& axis) {
            float sinTheta = std::sin(jtx::radians(theta));
            float cosTheta = std::cos(jtx::radians(theta));
            return jtx::Transform::rotate(sinTheta, cosTheta, axis);
        }

        static Transform rotateFromTo(const Vec3f& from, const Vec3f& to) {
            // Intermediate vector
            Vec3f refl;
            if (std::abs(from.x) < 0.72f && std::abs(to.x) < 0.72f) {
                refl = Vec3f(1, 0, 0);
            } else if (std::abs(from.y) < 0.72f && std::abs(to.y) < 0.72f) {
                refl = Vec3f(0, 1, 0);
            } else {
                refl = Vec3f(0, 0, 1);
            }
            Vec3f u = refl - from;
            Vec3f v = refl - to;

            Mat4 r;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    float uu = jtx::dot(u, u);
                    float vv = jtx::dot(v, v);
                    r[i][j] = ((i == j) ? 1.0f : 0.0f) -
                              (2 / uu) * u[i] * u[j] -
                              (2 / vv) * v[i] * v[j] +
                              (4 * jtx::dot(u, v)) / (uu * vv) * u[i] * v[j];
                }
            }

            return {r, r.transpose()};
        }

        // Note to self, PBRT calculates worldFromCamera, then inverts it
        // Old JTX calculated cameraFromWorld (and also was row-major)
        static Transform lookAt(const Point3f &pos, const Point3f &look, const Vec3f &up) {
            Vec3f dir = jtx::normalize(look - pos);
            ASSERT((jtx::cross(jtx::normalize(up), dir)).len() != 0);
            Vec3f right = jtx::normalize(jtx::cross(jtx::normalize(up), dir));
            Vec3f newUp = jtx::cross(dir, right);

            Mat4 m(right.x, newUp.x, dir.x, pos.x,
                   right.y, newUp.y, dir.y, pos.y,
                   right.z, newUp.z, dir.z, pos.z,
                   0, 0, 0, 1);
            return {jtx::invert(m), m};
        }
        //endregion

    private:
        Mat4 m;
        Mat4 mInv;
    };

    inline Transform inverse(const Transform &t) {
        return t.inverse();
    }

    inline Transform transpose(const Transform &t) {
        return t.transpose();
    }
}