#pragma once

#include <span>
#include <optional>
#include "numerical.hpp"
#include "vec4.hpp"
#include "math.hpp"

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

        static Mat4 diagonal(float d0, float d1, float d2, float d3) {
            Mat4 m;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (i != j) m[i][j] = 0;
                }
            }
            m[0][0] = d0;
            m[1][1] = d1;
            m[2][2] = d2;
            m[3][3] = d3;
            return m;
        }
        //endregion

        //region Binary operators
        std::span<const float> operator[](int i) const {
            return {m[i]};
        }

        std::span<float> operator[](int i) {
            return {m[i]};
        }

        Mat4 operator+(const Mat4 &other) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] += other[i][j];
                }
            }
            return res;
        }

        Mat4 operator+(const float scalar) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] += scalar;
                }
            }
            return res;
        }

        friend Mat4 operator+(const float scalar, const Mat4 &mat) {
            return mat + scalar;
        }

        Mat4 operator-(const Mat4 &other) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] -= other[i][j];
                }
            }
            return res;
        }

        Mat4 operator-(const float scalar) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] -= scalar;
                }
            }
            return res;
        }

        Mat4 operator*(const float scalar) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] *= scalar;
                }
            }
            return res;
        }

        friend Mat4 operator*(const float scalar, const Mat4 &mat) {
            return mat * scalar;
        }

        Mat4 operator/(const float scalar) const {
            ASSERT(scalar != 0.0f);
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] /= scalar;
                }
            }
            return res;
        }

        bool operator==(const Mat4 &other) const {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (m[i][j] != other[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool operator!=(const Mat4 &other) const {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (m[i][j] != other[i][j]) {
                        return true;
                    }
                }
            }
            return false;
        }
        //endregion

        //region Methods
        [[nodiscard]] bool isIdentity() const {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (i == j) {
                        if (m[i][j] != 1) return false;
                    } else {
                        if (m[i][j] != 0) return false;
                    }
                }
            }
            return true;
        }

        [[nodiscard]] inline Vec4f mul(const Vec4f &vec) const {
            Vec4f res;
            for (int i = 0; i < 4; ++i) {
                res[i] = jtx::innerProdf(m[i][0], vec[0], m[i][1], vec[1], m[i][2], vec[2], m[i][3], vec[3]);
            }
            return res;
        }

        [[nodiscard]] inline Mat4 mul(const Mat4 &mat) const {
            Mat4 res;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] = jtx::innerProdf(m[i][0], mat[0][j], m[i][1], mat[1][j], m[i][2], mat[2][j], m[i][3],
                                                mat[3][j]);
                }
            }
            return res;
        }

        Mat4 operator*(const Mat4 &other) const {
            return this->mul(other);
        }

        // PBRT
        [[nodiscard]] inline float determinant() const {
            float s0 = jtx::dop(m[0][0], m[1][1], m[1][0], m[0][1]);
            float s1 = jtx::dop(m[0][0], m[1][2], m[1][0], m[0][2]);
            float s2 = jtx::dop(m[0][0], m[1][3], m[1][0], m[0][3]);

            float s3 = jtx::dop(m[0][1], m[1][2], m[1][1], m[0][2]);
            float s4 = jtx::dop(m[0][1], m[1][3], m[1][1], m[0][3]);
            float s5 = jtx::dop(m[0][2], m[1][3], m[1][2], m[0][3]);

            float c0 = jtx::dop(m[2][0], m[3][1], m[3][0], m[2][1]);
            float c1 = jtx::dop(m[2][0], m[3][2], m[3][0], m[2][2]);
            float c2 = jtx::dop(m[2][0], m[3][3], m[3][0], m[2][3]);

            float c3 = jtx::dop(m[2][1], m[3][2], m[3][1], m[2][2]);
            float c4 = jtx::dop(m[2][1], m[3][3], m[3][1], m[2][3]);
            float c5 = jtx::dop(m[2][2], m[3][3], m[3][2], m[2][3]);

            return jtx::dop(s0, c5, s1, c4) + jtx::dop(s2, c3, -s3, c2) +
                   jtx::dop(s5, c0, s4, c1);
        }

        [[nodiscard]] inline Mat4 transpose() const {
            Mat4 res;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] = m[j][i];
                }
            }
            return res;
        }

        // PBRT
        [[nodiscard]] inline std::optional<Mat4> inverse() const {
            float s0 = jtx::dop(m[0][0], m[1][1], m[1][0], m[0][1]);
            float s1 = jtx::dop(m[0][0], m[1][2], m[1][0], m[0][2]);
            float s2 = jtx::dop(m[0][0], m[1][3], m[1][0], m[0][3]);

            float s3 = jtx::dop(m[0][1], m[1][2], m[1][1], m[0][2]);
            float s4 = jtx::dop(m[0][1], m[1][3], m[1][1], m[0][3]);
            float s5 = jtx::dop(m[0][2], m[1][3], m[1][2], m[0][3]);

            float c0 = jtx::dop(m[2][0], m[3][1], m[3][0], m[2][1]);
            float c1 = jtx::dop(m[2][0], m[3][2], m[3][0], m[2][2]);
            float c2 = jtx::dop(m[2][0], m[3][3], m[3][0], m[2][3]);

            float c3 = jtx::dop(m[2][1], m[3][2], m[3][1], m[2][2]);
            float c4 = jtx::dop(m[2][1], m[3][3], m[3][1], m[2][3]);
            float c5 = jtx::dop(m[2][2], m[3][3], m[3][2], m[2][3]);

            float det = jtx::dop(s0, c5, s1, c4) + jtx::dop(s2, c3, -s3, c2) +
                        jtx::dop(s5, c0, s4, c1);
            if (det == 0.0f) {
                return {};
            }

            float invDet = 1.0f / det;

            return {{invDet * jtx::innerProd(m[1][1], c5, m[1][3], c3, -m[1][2], c4),
                     invDet * jtx::innerProd(-m[0][1], c5, m[0][2], c4, -m[0][3], c3),
                     invDet * jtx::innerProd(m[3][1], s5, m[3][3], s3, -m[3][2], s4),
                     invDet * jtx::innerProd(-m[2][1], s5, m[2][2], s4, -m[2][3], s3),
                     invDet * jtx::innerProd(-m[1][0], c5, m[1][2], c2, -m[1][3], c1),
                     invDet * jtx::innerProd(m[0][0], c5, m[0][3], c1, -m[0][2], c2),
                     invDet * jtx::innerProd(-m[3][0], s5, m[3][2], s2, -m[3][3], s1),
                     invDet * jtx::innerProd(m[2][0], s5, m[2][3], s1, -m[2][2], s2),
                     invDet * jtx::innerProd(m[1][0], c4, m[1][3], c0, -m[1][1], c2),
                     invDet * jtx::innerProd(-m[0][0], c4, m[0][1], c2, -m[0][3], c0),
                     invDet * jtx::innerProd(m[3][0], s4, m[3][3], s0, -m[3][1], s2),
                     invDet * jtx::innerProd(-m[2][0], s4, m[2][1], s2, -m[2][3], s0),
                     invDet * jtx::innerProd(-m[1][0], c3, m[1][1], c1, -m[1][2], c0),
                     invDet * jtx::innerProd(m[0][0], c3, m[0][2], c0, -m[0][1], c1),
                     invDet * jtx::innerProd(-m[3][0], s3, m[3][1], s1, -m[3][2], s0),
                     invDet * jtx::innerProd(m[2][0], s3, m[2][2], s0, -m[2][1], s1)}};
        }

        [[nodiscard]] std::string toString() const {
            std::string res;
            for (auto i: m) {
                for (int j = 0; j < 4; ++j) {
                    res += std::to_string(i[j]) + " ";
                }
                res += "\n";
            }
            return res;
        }

        //endregion
    private:
        float m[4][4];
    };

    inline Vec4f mul(const Mat4 &mat, const Vec4f &vec) { return mat.mul(vec); }

    inline Mat4 mul(const Mat4 &a, const Mat4 &b) { return a.mul(b); }

    inline Mat4 transpose(const Mat4 &mat) { return mat.transpose(); }

    inline std::optional<Mat4> inverse(const Mat4 &mat) { return mat.inverse(); }

    inline Mat4 invert(const Mat4 &mat) {
        auto inv = inverse(mat);
        ASSERT(inv.has_value());
        return inv.value();
    }

    inline std::optional<Mat4> linearLS(const Mat4 &A, const Mat4 &B) {
        Mat4 AtA = Mat4::zero();
        Mat4 AtB = Mat4::zero();

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    AtA[i][j] += A[k][i] * A[k][j];
                    AtB[i][j] += A[k][i] * B[k][j];
                }
            }
        }

        auto AtA_inv = inverse(AtA);
        if (!AtA_inv.has_value()) { return {}; }
        return jtx::transpose((*AtA_inv).mul(AtB));
    }
}