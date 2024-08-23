#include <jtxlib/math/spherical.hpp>
#include "./tconstants.h"
#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace jtx;

//region Spherical Area
//region Spherical Area
TEST_CASE("Spherical Triangle Area", "[Spherical]") {
    Vec3f a(1, 0, 0);
    Vec3f b(0, 1, 0);
    Vec3f c(0, 0, 1);
    REQUIRE_THAT(sphericalTriangleArea(a, b, c), Catch::Matchers::WithinRel(1.5708f, T_EPS));
}

TEST_CASE("Spherical Quad Area", "[Spherical]") {
    Vec3f a(1, 0, 0);
    Vec3f b(0, 1, 0);
    Vec3f c(-1, 0, 0);
    Vec3f d(0, -1, 0);
    REQUIRE_THAT(sphericalQuadArea(a, b, c, d), Catch::Matchers::WithinRel(6.2832f, T_EPS));
}

TEST_CASE("Spherical To Cartesian", "[Spherical]") {
    float theta = jtx::radians(90.0f);
    float phi = jtx::radians(0.0f);
    Vec3f v = sphericalToCartesian(sin(theta), cos(theta), phi);
    REQUIRE_THAT(v.len(), Catch::Matchers::WithinRel(1.0f, T_EPS));
    REQUIRE(v.equals(Vec3f{1.0f, 0.0f, 0.0f}, T_EPS));
}
//endregion

//region Octahedral encoding
TEST_CASE("Octahedral Vec Constructor - Valid Input", "[Octahedral]") {
    const float OCT_EPS = 1e-2;

    SECTION("Valid Input") {
        Vec3f v(1, 0, 0);
        OctahedralVec octVec(v);
        auto result = Vec3f(octVec);
        REQUIRE(result.equals(v, OCT_EPS));
    }

    SECTION("Negative Z") {
        Vec3f v(0, 0, -1);
        OctahedralVec octVec(v);
        auto result = Vec3f(octVec);
        REQUIRE(result.equals(v, OCT_EPS));
    }

    SECTION("Diagonal") {
        Vec3f v(1, 1, 1);
        v.normalize();
        OctahedralVec octVec(v);
        auto result = Vec3f(octVec);
        REQUIRE(result.equals(v, OCT_EPS));
    }
}
//endregion

//region Square-Sphere Conversions

//endregion