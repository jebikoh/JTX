#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma once

#include <span>
#include <optional>
#include <jtxlib/math/constants.hpp>
#include <jtxlib/math/numerical.hpp>
#include <jtxlib/util/assert.hpp>
#include <jtxlib/math/vec4.hpp>
#include <jtxlib/math/vec3.hpp>
#include <jtxlib/math/vecmath.hpp>

#if defined(CUDA_ENABLED) && defined(__CUDA_ARCH__)

#include <cuda/std/optional>
#include <cuda/std/span>

#endif

namespace jtx {
    class Mat4 {
    public:
        float data[4][4];
        //region Constructors
        JTX_HOSTDEV Mat4() {
            for (auto &i: data) {
                for (float &j: i) {
                    j = 0.0f;
                }
            }
        }

        JTX_HOSTDEV explicit Mat4(float diag) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] = (i == j) ? diag : 0.0f;
                }
            }
        }

        JTX_HOSTDEV Mat4(const Mat4 &mat) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] = mat[i][j];
                }
            }
        }

        JTX_HOSTDEV Mat4(float m00, float m01, float m02, float m03,
                         float m10, float m11, float m12, float m13,
                         float m20, float m21, float m22, float m23,
                         float m30, float m31, float m32, float m33) {
            data[0][0] = m00;
            data[0][1] = m01;
            data[0][2] = m02;
            data[0][3] = m03;
            data[1][0] = m10;
            data[1][1] = m11;
            data[1][2] = m12;
            data[1][3] = m13;
            data[2][0] = m20;
            data[2][1] = m21;
            data[2][2] = m22;
            data[2][3] = m23;
            data[3][0] = m30;
            data[3][1] = m31;
            data[3][2] = m32;
            data[3][3] = m33;
        }

        JTX_HOSTDEV explicit Mat4(const float mat[4][4]) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] = mat[i][j];
                }
            }
        }

        JTX_HOSTDEV ~Mat4() = default;

        JTX_HOSTDEV static Mat4 identity() {
            return Mat4(1.0f);
        }

        JTX_HOSTDEV static Mat4 diagonal(float d0, float d1, float d2, float d3) {
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
#if defined(CUDA_ENABLED) && defined(__CUDA_ARCH__)
        JTX_HOSTDEV cuda::std::span<const float> operator[](int i) const {
            return {data[i]};
        }

        JTX_HOSTDEV cuda::std::span<float> operator[](int i) {
            return {data[i]};
        }
#else
        JTX_HOST std::span<const float> operator[](int i) const {
            return {data[i]};
        }

        JTX_HOST std::span<float> operator[](int i) {
            return {data[i]};
        }

#endif

        JTX_HOSTDEV Mat4 operator+(const Mat4 &other) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] += other[i][j];
                }
            }
            return res;
        }

        JTX_HOSTDEV Mat4 operator+(const float scalar) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] += scalar;
                }
            }
            return res;
        }

        JTX_HOSTDEV friend Mat4 operator+(const float scalar, const Mat4 &mat) {
            return mat + scalar;
        }

        JTX_HOSTDEV Mat4 operator-(const Mat4 &other) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] -= other[i][j];
                }
            }
            return res;
        }

        JTX_HOSTDEV Mat4 operator-(const float scalar) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] -= scalar;
                }
            }
            return res;
        }

        JTX_HOSTDEV Mat4 operator*(const float scalar) const {
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] *= scalar;
                }
            }
            return res;
        }

        JTX_HOSTDEV friend Mat4 operator*(const float scalar, const Mat4 &mat) {
            return mat * scalar;
        }

        JTX_HOSTDEV Mat4 operator/(const float scalar) const {
            ASSERT(scalar != 0.0f);
            Mat4 res = *this;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] /= scalar;
                }
            }
            return res;
        }

        JTX_HOSTDEV bool operator==(const Mat4 &other) const {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (data[i][j] != other[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        JTX_HOSTDEV bool operator!=(const Mat4 &other) const {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (data[i][j] != other[i][j]) {
                        return true;
                    }
                }
            }
            return false;
        }
        //endregion

        //region In-line Methods
        [[nodiscard]] JTX_HOSTDEV bool isIdentity() const {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (i == j) {
                        if (data[i][j] != 1) return false;
                    } else {
                        if (data[i][j] != 0) return false;
                    }
                }
            }
            return true;
        }

        [[nodiscard]] JTX_HOSTDEV Vec4f mul(const Vec4f &vec) const {
            Vec4f res;
            for (int i = 0; i < 4; ++i) {
                res[i] = jtx::innerProdf(data[i][0], vec[0], data[i][1], vec[1], data[i][2], vec[2], data[i][3],
                                         vec[3]);
            }
            return res;
        }

        [[nodiscard]] JTX_HOSTDEV Mat4 mul(const Mat4 &mat) const {
            Mat4 res;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] = jtx::innerProdf(data[i][0], mat[0][j], data[i][1], mat[1][j], data[i][2], mat[2][j],
                                                data[i][3],
                                                mat[3][j]);
                }
            }
            return res;
        }

        JTX_HOSTDEV Mat4 operator*(const Mat4 &other) const {
            return this->mul(other);
        }

        [[nodiscard]] JTX_HOSTDEV Mat4 transpose() const {
            Mat4 res;
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    res[i][j] = data[j][i];
                }
            }
            return res;
        }

        [[nodiscard]] JTX_HOSTDEV float determinant() const;

#if defined(CUDA_ENABLED) && defined(__CUDA_ARCH__)

        [[nodiscard]] JTX_HOSTDEV cuda::std::optional<Mat4> inverse() const;

#else

        [[nodiscard]] JTX_HOST std::optional<Mat4> inverse() const;

#endif
        //endregion
    };

    JTX_HOSTDEV JTX_INLINE Vec4f mul(const Mat4 &mat, const Vec4f &vec) { return mat.mul(vec); }

    JTX_HOSTDEV JTX_INLINE Mat4 mul(const Mat4 &a, const Mat4 &b) { return a.mul(b); }

    JTX_HOSTDEV JTX_INLINE Mat4 transpose(const Mat4 &mat) { return mat.transpose(); }

#if defined(CUDA_ENABLED) && defined(__CUDA_ARCH__)
    JTX_HOSTDEV JTX_INLINE cuda::std::optional<Mat4> inverse(const Mat4 &mat) { return mat.inverse(); }

    JTX_HOSTDEV JTX_INLINE cuda::std::optional<Mat4> linearLS(const Mat4 &A, const Mat4 &B) {
        Mat4 AtA = Mat4{};
        Mat4 AtB = Mat4{};

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
#else

    JTX_HOSTDEV JTX_INLINE std::optional<Mat4> inverse(const Mat4 &mat) { return mat.inverse(); }

    JTX_HOSTDEV JTX_INLINE std::optional<Mat4> linearLS(const Mat4 &A, const Mat4 &B) {
        Mat4 AtA = Mat4{};
        Mat4 AtB = Mat4{};

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

#endif

    JTX_HOSTDEV JTX_INLINE Mat4 invert(const Mat4 &mat) {
        auto inv = inverse(mat);
        ASSERT(inv.has_value());
        return inv.value();
    }

    //region Matrix Transformations
    JTX_HOSTDEV JTX_INLINE Mat4 translate(const float delta) {
        return {
                1.0f, 0.0f, 0.0f, delta,
                0.0f, 1.0f, 0.0f, delta,
                0.0f, 0.0f, 1.0f, delta,
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    JTX_HOSTDEV JTX_INLINE Mat4 translate(float x, float y, float z) {
        return {
                1.0f, 0.0f, 0.0f, x,
                0.0f, 1.0f, 0.0f, y,
                0.0f, 0.0f, 1.0f, z,
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    JTX_HOSTDEV JTX_INLINE Mat4 translate(const jtx::Vec3f &v) {
        return translate(v.x, v.y, v.z);
    }

    JTX_HOSTDEV JTX_INLINE Mat4 scale(float s) {
        return Mat4::diagonal(s, s, s, 1.0f);
    }

    JTX_HOSTDEV JTX_INLINE Mat4 scale(float x, float y, float z) {
        return Mat4::diagonal(x, y, z, 1.0f);
    }

    JTX_HOSTDEV JTX_INLINE Mat4 scale(const jtx::Vec3f &v) {
        return Mat4::diagonal(v.x, v.y, v.z, 1.0f);
    }

    JTX_HOSTDEV JTX_INLINE Mat4 rotateX(float theta) {
        float sinTheta = jtx::sin(jtx::radians(theta));
        float cosTheta = jtx::cos(jtx::radians(theta));
        return {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, cosTheta, -sinTheta, 0.0f,
                0.0f, sinTheta, cosTheta, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    JTX_HOSTDEV JTX_INLINE Mat4 rotateY(float theta) {
        float sinTheta = jtx::sin(jtx::radians(theta));
        float cosTheta = jtx::cos(jtx::radians(theta));
        return {
                cosTheta, 0.0f, sinTheta, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                -sinTheta, 0.0f, cosTheta, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    JTX_HOSTDEV JTX_INLINE Mat4 rotateZ(float theta) {
        float sinTheta = jtx::sin(jtx::radians(theta));
        float cosTheta = jtx::cos(jtx::radians(theta));
        return {
                cosTheta, -sinTheta, 0.0f, 0.0f,
                sinTheta, cosTheta, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    JTX_HOSTDEV Mat4 rotate(float sinTheta, float cosTheta, const Vec3f &axis);

    JTX_HOSTDEV Mat4 rotate(float theta, const jtx::Vec3f &axis);

    JTX_HOSTDEV Mat4 rotateFromTo(const Vec3f &from, const Vec3f &to);

    JTX_HOSTDEV JTX_INLINE Mat4
    lookAt(const Vec3f &right, const Vec3f &vup, const Vec3f &direction, const Vec3f &position) {
        return {
                right.x, right.y, right.z, -jtx::dot(right, position),
                vup.x, vup.y, vup.z, -jtx::dot(vup, position),
                -direction.x, -direction.y, -direction.z, jtx::dot(direction, position),
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    JTX_HOSTDEV JTX_INLINE Mat4 lookAt(const Vec3f &position, const Vec3f &target, const Vec3f &up) {
        auto direction = (target - position).normalize();
        Vec3f right = jtx::cross(direction, up).normalize();
        Vec3f vup = jtx::cross(right, direction).normalize();
        return lookAt(right, vup, direction, position);
    }

    JTX_HOSTDEV JTX_INLINE Mat4 perspective(float fov, float aspect, float near, float far) {
        float invTanAng = 1.0f / std::tan(jtx::radians(fov) / 2.0f);
        return {
                invTanAng / aspect, 0.0f, 0.0f, 0.0f,
                0.0f, invTanAng, 0.0f, 0.0f,
                0.0f, 0.0f, (far + near) / (near - far), 2.0f * far * near / (near - far),
                0.0f, 0.0f, -1.0f, 0.0f
        };
    }

    JTX_HOSTDEV JTX_INLINE Mat4 orthographic(float left, float right, float bottom, float top, float near, float far) {
        return {
                2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
                0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
                0.0f, 0.0f, -2.0f / (far - near), -(far + near) / (far - near),
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    //endregion

    JTX_HOST std::string toString(const Mat4 &mat);
}
#pragma clang diagnostic pop