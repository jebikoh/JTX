#pragma once

#include <cmath>
#include <stdexcept>
#include "cblas.h"
//#include "mat4.hpp"

namespace JTX::Util {
    class Vec4 {
    public:
        float x, y, z, w;

        Vec4(): x(0), y(0), z(0), w(0) {};
        Vec4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {};
        ~Vec4() = default;

        inline bool operator==(const Vec4& other) const {
            return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
        }
        inline bool operator!=(const Vec4& other) const {
            return !(*this == other);
        }
        inline Vec4 operator+(const Vec4& other) const {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }
        inline Vec4 operator-(const Vec4& other) const {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }
        inline Vec4 operator*(const Vec4& other) const {
            return {x * other.x, y * other.y, z * other.z, w * other.w};
        }
        inline Vec4 operator+=(const Vec4& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }
        inline Vec4 operator-=(const Vec4& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }
        inline Vec4 operator*=(const Vec4& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }

        inline float dot(const Vec4& other) {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }
        inline float dot(const float _x, const float _y, const float _z, const float _w) {
            return this->x * _x + this->y * _y + this->z * _z + this->w * _w;
        }
        [[nodiscard]] inline float len() const { return std::sqrt(x * x + y * y + z * z + w * w); }

        inline Vec4& normalize() {
            float l = len();
            if (l != 0) { x/= l; y /= l; z /= l; w /= l; }
            else throw std::runtime_error("Cannot normalize a zero vector");
            return *this;
        }

        inline Vec4 normalized() const {
            float l = len();
            if (l != 0) { return {x / l, y / l, z / l, w / l}; }
            else throw std::runtime_error("Cannot normalize a zero vector");
        }

//        // TODO: Profile this. BLAS might take longer than an unrolled loop here since M is only 4x4
//        void applyTransform(const JTX::Util::Mat4* tf) {
//            float v[4] = {x, y, z, w};
//            float result[4];
//            cblas_sgemv(CblasRowMajor, CblasNoTrans, 4, 4, 1.0f,
//                        reinterpret_cast<const float*>(tf->data), 4, v, 1, 0.0f, result, 1);
//            x = result[0];
//            y = result[1];
//            z = result[2];
//            w = result[3];
//        }
    };
}

