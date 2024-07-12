#include <jtxlib/math/mat4.hpp>
#include <jtxlib/math/math.hpp>

float jtx::Mat4::determinant() const {
    float s0 = jtx::dop(data[0][0], data[1][1], data[1][0], data[0][1]);
    float s1 = jtx::dop(data[0][0], data[1][2], data[1][0], data[0][2]);
    float s2 = jtx::dop(data[0][0], data[1][3], data[1][0], data[0][3]);

    float s3 = jtx::dop(data[0][1], data[1][2], data[1][1], data[0][2]);
    float s4 = jtx::dop(data[0][1], data[1][3], data[1][1], data[0][3]);
    float s5 = jtx::dop(data[0][2], data[1][3], data[1][2], data[0][3]);

    float c0 = jtx::dop(data[2][0], data[3][1], data[3][0], data[2][1]);
    float c1 = jtx::dop(data[2][0], data[3][2], data[3][0], data[2][2]);
    float c2 = jtx::dop(data[2][0], data[3][3], data[3][0], data[2][3]);

    float c3 = jtx::dop(data[2][1], data[3][2], data[3][1], data[2][2]);
    float c4 = jtx::dop(data[2][1], data[3][3], data[3][1], data[2][3]);
    float c5 = jtx::dop(data[2][2], data[3][3], data[3][2], data[2][3]);

    return jtx::dop(s0, c5, s1, c4) + jtx::dop(s2, c3, -s3, c2) +
           jtx::dop(s5, c0, s4, c1);
}


std::optional<jtx::Mat4> jtx::Mat4::inverse() const {
    float s0 = jtx::dop(data[0][0], data[1][1], data[1][0], data[0][1]);
    float s1 = jtx::dop(data[0][0], data[1][2], data[1][0], data[0][2]);
    float s2 = jtx::dop(data[0][0], data[1][3], data[1][0], data[0][3]);

    float s3 = jtx::dop(data[0][1], data[1][2], data[1][1], data[0][2]);
    float s4 = jtx::dop(data[0][1], data[1][3], data[1][1], data[0][3]);
    float s5 = jtx::dop(data[0][2], data[1][3], data[1][2], data[0][3]);

    float c0 = jtx::dop(data[2][0], data[3][1], data[3][0], data[2][1]);
    float c1 = jtx::dop(data[2][0], data[3][2], data[3][0], data[2][2]);
    float c2 = jtx::dop(data[2][0], data[3][3], data[3][0], data[2][3]);

    float c3 = jtx::dop(data[2][1], data[3][2], data[3][1], data[2][2]);
    float c4 = jtx::dop(data[2][1], data[3][3], data[3][1], data[2][3]);
    float c5 = jtx::dop(data[2][2], data[3][3], data[3][2], data[2][3]);

    float det = jtx::dop(s0, c5, s1, c4) + jtx::dop(s2, c3, -s3, c2) +
                jtx::dop(s5, c0, s4, c1);
    if (det == 0.0f) {
        return {};
    }

    float invDet = 1.0f / det;

    return {{invDet * jtx::innerProd(data[1][1], c5, data[1][3], c3, -data[1][2], c4),
             invDet * jtx::innerProd(-data[0][1], c5, data[0][2], c4, -data[0][3], c3),
             invDet * jtx::innerProd(data[3][1], s5, data[3][3], s3, -data[3][2], s4),
             invDet * jtx::innerProd(-data[2][1], s5, data[2][2], s4, -data[2][3], s3),
             invDet * jtx::innerProd(-data[1][0], c5, data[1][2], c2, -data[1][3], c1),
             invDet * jtx::innerProd(data[0][0], c5, data[0][3], c1, -data[0][2], c2),
             invDet * jtx::innerProd(-data[3][0], s5, data[3][2], s2, -data[3][3], s1),
             invDet * jtx::innerProd(data[2][0], s5, data[2][3], s1, -data[2][2], s2),
             invDet * jtx::innerProd(data[1][0], c4, data[1][3], c0, -data[1][1], c2),
             invDet * jtx::innerProd(-data[0][0], c4, data[0][1], c2, -data[0][3], c0),
             invDet * jtx::innerProd(data[3][0], s4, data[3][3], s0, -data[3][1], s2),
             invDet * jtx::innerProd(-data[2][0], s4, data[2][1], s2, -data[2][3], s0),
             invDet * jtx::innerProd(-data[1][0], c3, data[1][1], c1, -data[1][2], c0),
             invDet * jtx::innerProd(data[0][0], c3, data[0][2], c0, -data[0][1], c1),
             invDet * jtx::innerProd(-data[3][0], s3, data[3][1], s1, -data[3][2], s0),
             invDet * jtx::innerProd(data[2][0], s3, data[2][2], s0, -data[2][1], s1)}};
}
