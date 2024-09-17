#include <jtxlib/math/mat4.hpp>
#include <jtxlib/math/transform.hpp>
#include "tconstants.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Mat4 default constructor is identity matrix", "[Mat4]") {
    jtx::Mat4 mat{1.0f};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            REQUIRE(mat[i][j] == (i == j ? 1.0f : 0.0f));
    }

    bool is_identity = mat.isIdentity();
    REQUIRE(is_identity);
}

TEST_CASE("Mat4 copy constructor", "[Mat4]") {
    jtx::Mat4 mat{1.0f};
    jtx::Mat4 matCopy(mat);

    REQUIRE(matCopy == mat);
    REQUIRE(matCopy.isIdentity());
}

TEST_CASE("Mat4 individual float constructor", "[Mat4]") {
    jtx::Mat4 mat{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    REQUIRE(mat.isIdentity());
}

TEST_CASE("Mat4 float array constructor", "[Mat4]") {
    float data[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 1.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f}};
    jtx::Mat4 mat{data};
    REQUIRE(mat.isIdentity());
}

TEST_CASE("Mat4 (in)equality operators", "[Mat4]") {
    jtx::Mat4 m1{};
    jtx::Mat4 m2{};
    m2[0][0] = 2.0f;

    jtx::Mat4 m3{};

    REQUIRE(m1 != m2);
    REQUIRE(m1 == m3);
}

TEST_CASE("Mat4 zero matrix", "[Mat4]") {
    jtx::Mat4 mat = jtx::Mat4{};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            REQUIRE(mat[i][j] == 0.0f);
    }
}

TEST_CASE("Mat4 diagonal", "[Mat4]") {
    jtx::Mat4 diag = jtx::Mat4::diagonal(2, 2, 2, 2);
    jtx::Mat4 diag_ref{2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2};
    REQUIRE(diag == diag_ref);
}

TEST_CASE("Mat4 addition operators", "[Mat4]") {
    jtx::Mat4 mat1{1.0f};
    jtx::Mat4 mat2{1.0f};
    float scalar = 2.0f;

    jtx::Mat4 sum = mat1 + mat2;
    REQUIRE(sum == jtx::Mat4::diagonal(2, 2, 2, 2));

    jtx::Mat4 sum2 = sum + scalar;
    jtx::Mat4 sum2_ref{4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4};
    REQUIRE(sum2 == sum2_ref);

    jtx::Mat4 sum3 = scalar + sum2;
    jtx::Mat4 sum3_ref{6, 4, 4, 4, 4, 6, 4, 4, 4, 4, 6, 4, 4, 4, 4, 6};
    REQUIRE(sum3 == sum3_ref);
}

TEST_CASE("Mat4 subtraction operators", "[Mat4]") {
    jtx::Mat4 mat1{};
    jtx::Mat4 mat2{};
    float scalar = 2.0f;

    jtx::Mat4 diff = mat1 - mat2;
    REQUIRE(diff == jtx::Mat4{});

    jtx::Mat4 diff2 = diff - scalar;
    jtx::Mat4 diff2_ref{-2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0};
    REQUIRE(diff2 == diff2_ref);
}

TEST_CASE("Mat4 scalar multiplication operators", "[Mat4]") {
    jtx::Mat4 mat{1.0f};
    float scalar = 2.0f;

    jtx::Mat4 prod = mat * scalar;
    jtx::Mat4 prod2 = scalar * mat;

    jtx::Mat4 prod_ref = jtx::Mat4::diagonal(2, 2, 2, 2);
    REQUIRE(prod == prod_ref);
    REQUIRE(prod2 == prod_ref);
}

TEST_CASE("Mat4 scalar division operators", "[Mat4]") {
    jtx::Mat4 mat{1.0f};
    float scalar = 2.0f;

    jtx::Mat4 quot = mat / scalar;
    jtx::Mat4 quot_ref = jtx::Mat4::diagonal(0.5, 0.5, 0.5, 0.5);
    REQUIRE(quot == quot_ref);
}

TEST_CASE("Mat4 isIdentity", "[Mat4]") {
    jtx::Mat4 mat{1.0f};
    REQUIRE(mat.isIdentity());

    jtx::Mat4 mat2{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    REQUIRE(mat2.isIdentity());

    jtx::Mat4 mat3{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f};
    REQUIRE_FALSE(mat3.isIdentity());
}

TEST_CASE("Mat4 isNaN", "[Mat4]") {
    jtx::Mat4 mat{1.0f};
    mat[0][0] = std::numeric_limits<float>::quiet_NaN();
    REQUIRE(mat.hasNaN());
}

TEST_CASE("Mat4 mul (Vec4f)", "[Mat4]") {
    jtx::Mat4 mat{1.0f};
    jtx::Vec4f vec{1.0f, 2.0f, 3.0f, 4.0f};

    jtx::Vec4f prod = mat.mul(vec);
    jtx::Vec4f prod_ref{1.0f, 2.0f, 3.0f, 4.0f};
    REQUIRE(prod == prod_ref);
}

TEST_CASE("Mat4 mul and * operator (Mat4)", "[Mat4]") {
    jtx::Mat4 identity{1.0f};
    jtx::Mat4 mat2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                   16.0f};

    jtx::Mat4 prod = identity.mul(mat2);
    REQUIRE(prod == mat2);

    jtx::Mat4 prod2 = identity * mat2;
    REQUIRE(prod2 == mat2);
}

TEST_CASE("Mat4 determinant", "[Mat4]") {
    jtx::Mat4 mat{2, 1, 0, 3, 4, -1, 2, 0, -3, 2, 1, 5, 1, 0, -2, 3};
    REQUIRE_THAT(mat.determinant(), Catch::Matchers::WithinRel(-85.0f, T_EPS));
}

TEST_CASE("Mat4 transpose", "[Mat4]") {
    jtx::Mat4 mat{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    jtx::Mat4 transposed = mat.transpose();
    jtx::Mat4 ref = jtx::Mat4{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

    REQUIRE(transposed == ref);
    REQUIRE(transposed.transpose() == mat);
}

TEST_CASE("Mat4 inverse", "[Mat4]") {
    jtx::Mat4 mat{1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1};
    jtx::Mat4 inv = jtx::invert(mat);
    jtx::Mat4 ref{0.25f, 0.25f, 0.25f, -0.25f, 0.25f, 0.25f, -0.25f, 0.25f, 0.25f, -0.25f, 0.25f, 0.25f, -0.25f, 0.25f,
                  0.25f, 0.25f};
    jtx::Mat4 identity{1.0f};
    REQUIRE(inv == ref);
    REQUIRE(inv * mat == identity);
    REQUIRE(mat * inv == identity);
}

TEST_CASE("Mat4 Linear LS", "[Mat4]") {
    // TODO: write linear LS equation
}

TEST_CASE("Mat4 Translations", "[Mat4]") {
    auto mat1 = jtx::translate(1.0f, 2.0f, 3.0f);
    auto mat2 = jtx::translate(jtx::Vec3f{1.0f, 2.0f, 3.0f});
    auto mat3 = jtx::translate(2.0f);

    jtx::Mat4 ref1_2 = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    jtx::Mat4 ref3 = {
        1.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 1.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 1.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    REQUIRE(mat1 == ref1_2);
    REQUIRE(mat2 == ref1_2);
    REQUIRE(mat3 == ref3);
}

TEST_CASE("Mat4 Scale", "[Mat4]") {
    auto mat1 = jtx::scale(1.0f, 2.0f, 3.0f);
    auto mat2 = jtx::scale(jtx::Vec3f{1.0f, 2.0f, 3.0f});
    auto mat3 = jtx::scale(2.0f);

    jtx::Mat4 ref1_2 = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    jtx::Mat4 ref3 = {
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    REQUIRE(mat1 == ref1_2);
    REQUIRE(mat2 == ref1_2);
    REQUIRE(mat3 == ref3);
}

TEST_CASE("Mat4 rotate XYZ", "[Mat4]") {
    SECTION("ROTATE X") {
        auto mat1 = jtx::rotateX(90.0f);
        jtx::Mat4 ref = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        REQUIRE(mat1.equals(ref, T_EPS));
    }

    SECTION("ROTATE Y") {
        auto mat1 = jtx::rotateY(90.0f);
        jtx::Mat4 ref = {
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        REQUIRE(mat1.equals(ref, T_EPS));
    }

    SECTION("ROTATE Z") {
        auto mat1 = jtx::rotateZ(90.0f);
        jtx::Mat4 ref = {
            0.0f, -1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        REQUIRE(mat1.equals(ref, T_EPS));
    }
}

TEST_CASE("Mat4 rotate", "[Mat4]") {
    jtx::Mat4 ref = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};

    SECTION("Rotate via sin theta and cos theta") {
        float sinTheta = std::sin(jtx::radians(90.0f));
        float cosTheta = std::cos(jtx::radians(90.0f));
        jtx::Vec3f axis = {1.0f, 0.0f, 0.0f};
        auto mat = jtx::rotate(sinTheta, cosTheta, axis);
        REQUIRE(mat.equals(ref, T_EPS));
    }

    SECTION("Rotate via theta and axis") {
        float theta = 90.0f;
        jtx::Vec3f axis = {1.0f, 0.0f, 0.0f};
        auto mat = jtx::rotate(theta, axis);
        REQUIRE(mat.equals(ref, T_EPS));
    }
}

TEST_CASE("Mat4 rotate from to", "[Mat4]") {
    jtx::Vec3f from = {1.0f, 0.0f, 0.0f};
    jtx::Vec3f to = {0.0f, 1.0f, 0.0f};
    auto mat1 = jtx::rotateFromTo(from, to);

    jtx::Vec4f result = mat1.mul(jtx::Vec4f{1.0f, 0.0f, 0.0f, 1.0f});
    jtx::Vec4f ref{0.0f, 1.0f, 0.0f, 0.0f};

    REQUIRE(result.equals(ref, T_EPS));
}

TEST_CASE("Mat4 lookAt", "[Mat4]") {
    jtx::Vec3f position = {0.0f, 0.0f, 1.0f};
    jtx::Vec3f target = {0.0f, 0.0f, 0.0f};
    jtx::Vec3f up = {0.0f, 1.0f, 0.0f};

    auto mat1 = jtx::lookAt(position, target, up);
    jtx::Mat4 ref = {
            -1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
    };

    REQUIRE(mat1.equals(ref, T_EPS));
}

TEST_CASE("Mat4 perspective projection", "[Mat4]") {
    float fov    = 60.0f;
    float aspect = 16.0f / 9.0f;
    float near   = 0.1f;
    float far    = 100.0f;

    auto mat = jtx::perspective(fov, aspect, near, far);
    jtx::Mat4 ref = {
            0.974279f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.732051f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.002002f, -0.2002002f,
            0.0f, 0.0f, -1.0f, 0.0f
    };
    REQUIRE(mat.equals(ref, T_EPS));
}

TEST_CASE("Mat4 orthographic projection", "[Mat4]") {
    float top    = 1.0f;
    float bottom = -1.0f;
    float left   = -1.0f;
    float right  = 1.0f;
    float near   = 0.1f;
    float far    = 100.0f;

    auto mat = jtx::orthographic(left, right, top, bottom, near, far);
    // Reference from GLM, so we have to transpose
    jtx::Mat4 ref = {
            1.000000f, 0.000000f, 0.000000f, 0.000000f,
            0.000000f, 1.000000f, 0.000000f, 0.00000f,
            0.000000f, 0.000000f, -0.020020f, 0.000000f,
            -0.000000, -0.000000, -1.002002, 1.000000,
    };
    ref = ref.transpose();

    REQUIRE(mat.equals(ref, T_EPS));
}

// Transform tests
TEST_CASE("Transform matrix constructor", "[Transform]") {
    SECTION("Invertible Matrix") {
        jtx::Mat4 m = jtx::Mat4{1.0f};
        jtx::Transform t{m};
        REQUIRE(t.getInverseMatrix().isIdentity());
    }

    SECTION("Non-Invertible Matrix") {
        jtx::Mat4 m = jtx::Mat4{1.0f};
        m[0][0] = 0.0f;
        jtx::Transform t{m};
        REQUIRE(t.getInverseMatrix().hasNaN());
    }
}

TEST_CASE("Transform isIdentity", "[Transform]") {
    jtx::Mat4 m{1.0f};
    jtx::Mat4 mInv{1.0f};
    jtx::Transform t{m, mInv};
    REQUIRE(t.isIdentity());
}

TEST_CASE("Transform inverse", "[Transform]") {
    jtx::Mat4 m{1.0f};
    jtx::Mat4 mInv{2.0f};
    jtx::Transform t{m, mInv};
    t = t.inverse();
    REQUIRE(t.getMatrix() == mInv);
    REQUIRE(t.getInverseMatrix() == m);
}

TEST_CASE("Transform transpose", "[Transform]") {
    jtx::Mat4 m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    jtx::Mat4 mT{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
    jtx::Transform t{m, mT};
    t = t.transpose();
    REQUIRE(t.getMatrix() == mT);
    REQUIRE(t.getInverseMatrix() == m);
}

TEST_CASE("Transform (in)equality", "[Transform]") {
    SECTION("Equality: equal matrices") {
        jtx::Mat4 m{1.0f};
        jtx::Transform t1{m};
        jtx::Transform t2{m};
        REQUIRE(t1 == t2);
    }

    SECTION("Equality: unequal matrices") {
        jtx::Mat4 m1{1.0f};
        jtx::Mat4 m2{2.0f};
        jtx::Transform t1{m1};
        jtx::Transform t2{m2};
        REQUIRE_FALSE(t1 == t2);
    }

    SECTION("Inequality: equal matrices") {
        jtx::Mat4 m{1.0f};
        jtx::Transform t1{m};
        jtx::Transform t2{m};
        REQUIRE_FALSE(t1 != t2);
    }

    SECTION("Inequality: unequal matrices") {
        jtx::Mat4 m1{1.0f};
        jtx::Mat4 m2{2.0f};
        jtx::Transform t1{m1};
        jtx::Transform t2{m2};
        REQUIRE(t1 != t2);
    }
}

// This one just makes sure the applicators work per target class
TEST_CASE("Transform apply", "[Transform]") {
    SECTION("Point") {
        jtx::Mat4 m{1.0f};
        jtx::Transform t{m};
        jtx::Vec3f point{1.0f, 2.0f, 3.0f};

        jtx::Vec3f result = t.applyToPoint(point);
        REQUIRE(result == point);

        result = t.applyInverseToPoint(point);
        REQUIRE(result == point);
    }

    SECTION("Vector") {
        jtx::Mat4 m{1.0f};
        jtx::Transform t{m};
        jtx::Vec3f vec{1.0f, 2.0f, 3.0f};

        jtx::Vec3f result = t.applyToNormal(vec);
        REQUIRE(result == vec);

        result = t.applyInverseToNormal(vec);
        REQUIRE(result == vec);
    }

    SECTION("Normal") {
        jtx::Mat4 m{1.0f};
        jtx::Transform t{m};
        jtx::Normal3f normal{1.0f, 2.0f, 3.0f};

        jtx::Normal3f result = t.applyToNormal(normal);
        REQUIRE(result == normal);

        result = t.applyInverseToNormal(normal);
        REQUIRE(result == normal);
    }

    SECTION("Ray") {
        jtx::Rayf ray{jtx::Point3f{1.0f, 2.0f, 3.0f}, jtx::Vec3f{1.0f, 0.0f, 0.0f}};
        auto m = jtx::Mat4{1.0f};
        jtx::Transform t{m};

        auto result = t.applyToRay(ray);
        REQUIRE(result == ray);
        result = t.applyInverseToRay(ray);
        REQUIRE(result == ray);
    }

    SECTION("Ray Differential") {
        jtx::RayfDifferential ray{jtx::Point3f{1.0f, 2.0f, 3.0f}, jtx::Vec3f{1.0f, 0.0f, 0.0f}};
        auto m = jtx::Mat4{1.0f};
        jtx::Transform t{m};

        auto result = t.applyToRayDiff(ray);
        REQUIRE(result == ray);
        result = t.applyInverseToRayDiff(ray);
        REQUIRE(result == ray);
    }

    SECTION("BBox") {
        jtx::BBox3f bbox{jtx::Point3f{1.0f, 2.0f, 3.0f}, jtx::Point3f{4.0f, 5.0f, 6.0f}};
        auto m = jtx::Mat4{1.0f};
        jtx::Transform t{m};

        auto result = t.applyToBBox(bbox);
        REQUIRE(result == bbox);
        result = t.applyInverseToBBox(bbox);
        REQUIRE(result == bbox);
    }

    SECTION("Normal (using rotate)") {
        jtx::Normal3f normal{1.0f, 0.0f, 0.0f};
        jtx::Mat4 m = jtx::rotateY(90.0f);
        jtx::Mat4 mInv = jtx::rotateY(-90.0f).transpose();
        auto ref = mInv.mul(jtx::Vec4f{normal.x, normal.y, normal.z, 1.0f});

        jtx::Transform t{m};
        auto result = t.applyToNormal(normal);


        REQUIRE(result.equals(jtx::Vec3f(ref), T_EPS));
    }
}

// These tests check the application of the transform and its inverse preserve the value
// (So this also tests the apply...() methods from Mat4
// The actual transformations are tested in the Mat4 tests
TEST_CASE("Transform translate", "[Transform]") {
    jtx::Transform t = jtx::Transform::translate(1.0f);
    jtx::Vec3f point{1.0f, 2.0f, 3.0f};
    jtx::Vec3f result = t.applyToPoint(point);
    result = t.applyInverseToPoint(result);
    REQUIRE(result.equals(point, T_EPS));
}

TEST_CASE("Transform scale", "[Transform]") {
    jtx::Transform t = jtx::Transform::scale(1.0f, 2.0f, 3.0f);
    jtx::Vec3f point{1.0f, 2.0f, 3.0f};
    jtx::Vec3f result = t.applyToPoint(point);
    result = t.applyInverseToPoint(result);
    REQUIRE(result.equals(point, T_EPS));
}

TEST_CASE("Transform rotateXYZ", "[Transform]") {
    jtx::Transform t = jtx::Transform::rotateX(90.0f);
    jtx::Vec3f point{1.0f, 2.0f, 3.0f};
    jtx::Vec3f result = t.applyToPoint(point);
    result = t.applyInverseToPoint(result);
    REQUIRE(result.equals(point, T_EPS));
}

TEST_CASE("Transform rotate", "[Transform]") {
    jtx::Transform t = jtx::Transform::rotate(90.0f, jtx::Vec3f{1.0f, 0.0f, 0.0f});
    jtx::Vec3f point{1.0f, 2.0f, 3.0f};
    jtx::Vec3f result = t.applyToPoint(point);
    result = t.applyInverseToPoint(result);
    REQUIRE(result.equals(point, T_EPS));
}

TEST_CASE("Transform rotateFromTo", "[Transform]") {
    jtx::Vec3f from = {1.0f, 0.0f, 0.0f};
    jtx::Vec3f to = {0.0f, 1.0f, 0.0f};
    auto t = jtx::Transform::rotateFromTo(from, to);

    auto result = t.applyToVec(from);

    result = t.applyInverseToVec(result);
    REQUIRE(result.equals(from, T_EPS));
}

// Transform class calculates lookAt in reverse.
// This checks to make sure it's consistent with Mat4
TEST_CASE("Transform lookAt", "[Transform]") {
    jtx::Vec3f position = {0.0f, 0.0f, 1.0f};
    jtx::Vec3f target = {0.0f, 0.0f, 0.0f};
    jtx::Vec3f up = {0.0f, 1.0f, 0.0f};

    auto mat1 = jtx::lookAt(position, target, up);
    auto mat2 = jtx::Transform::lookAt(position, target, up);

    REQUIRE(mat1.equals(mat2.getMatrix(), T_EPS));
    auto mat1_inv = jtx::inverse(mat1);
    REQUIRE(mat1_inv.has_value());
    REQUIRE(mat1_inv.value().equals(mat2.getInverseMatrix(), T_EPS));
}
