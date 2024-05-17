#pragma once

#include<cblas.h>
#include<cmath>

namespace JTX::Util {
    enum class Axis {
        X = 0,
        Y = 1,
        Z = 2
    };

    class Mat4 {
    public:
        float data[4][4]{};

        Mat4();
        Mat4(float d00, float d01, float d02, float d03,
             float d10, float d11, float d12, float d13,
             float d20, float d21, float d22, float d23,
             float d30, float d31, float d32, float d33);
        ~Mat4() = default;

        bool operator== (const Mat4& other) const;
        bool operator!= (const Mat4& other) const;
        inline float* operator[](int index) { return data[index]; };
        inline const float* operator[](int index) const { return data[index]; };

        static Mat4 rotation(float rad, Axis axis);
        static Mat4 translation(float x, float y, float z);
        static Mat4 scale(float x, float y, float z);

        static Mat4 matmul(const Mat4& m1, const Mat4& m2);
        Mat4 operator* (const Mat4& other) const;
    };
}