#pragma once

#include "numerical.hpp"
#include "vec4.hpp"

namespace jtx {
    class Mat4 {
    public:
        //region Constructors
        Mat4() {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    m[i][j] = (i == j) ? 1.0f : 0.0f;
                }
            }
        }

        Mat4(const Mat4 &mat) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    m[i][j] = mat[i][j];
                }
            }
        }

        Mat4(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33) {
            m[0][0] = m00;
            m[0][1] = m01;
            m[0][2] = m02;
            m[0][3] = m03;
            m[1][0] = m10;
            m[1][1] = m11;
            m[1][2] = m12;
            m[1][3] = m13;
            m[2][0] = m20;
            m[2][1] = m21;
            m[2][2] = m22;
            m[2][3] = m23;
            m[3][0] = m30;
            m[3][1] = m31;
            m[3][2] = m32;
            m[3][3] = m33;
        }

        explicit Mat4(const float mat[4][4]) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    m[i][j] = mat[i][j];
                }
            }
        }

        ~Mat4() = default;

        static Mat4 zero() {
            Mat4 m;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    m[i][j] = 0.0f;
                }
            }
            return m;
        }

        static Mat4 diagonal(float value) {
            Mat4 m;
            for (int i = 0; i < 4; ++i) {
                m[i][i] = value;
            }
            return m;
        }
        //endregion
        
        //region Methods
        [[nodiscard]] bool isIdentity() const {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (i == j && m[i][j] != 1.0f) {
                        return false;
                    } else {
                        if (m[i][j] != 0.0f) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        //endregion
    private:
        float m[4][4]{};
    };
}