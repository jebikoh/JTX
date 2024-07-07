#pragma once

#include "./matrix.hpp"
#include "./vec3.hpp"
#include "./vecmath.hpp"


namespace jtx {
    class Transform {
    public:
        //region Constructors
        Transform() = default;

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