#include "./matrix.hpp"


float jtx::Mat4::determinant() const {
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


std::optional<jtx::Mat4> jtx::Mat4::inverse() const {
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
