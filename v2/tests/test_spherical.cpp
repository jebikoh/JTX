#include "../src/util/spherical.hpp"
#include "../src/util/constants.hpp"
#include "./tconstants.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("sphericalTriangleArea", "[spherical]") {
    jtx::Vec3f a(1.0f, 0.0f, 0.0f);
    jtx::Vec3f b(0.0f, 1.0f, 0.0f);
    jtx::Vec3f c(0.0f, 0.0f, 1.0f);

    REQUIRE_THAT(jtx::sphericalTriangleArea(a, b, c), Catch::Matchers::WithinRel(jtx::PI_F / 2, T_EPS));
}

TEST_CASE("sphericalQuadArea", "[spherical]") {
    jtx::Vec3f a(1.0f, 0.0f, 0.0f);
    jtx::Vec3f b(0.0f, 1.0f, 0.0f);
    jtx::Vec3f c(-1.0f, 0.0f, 0.0f);
    jtx::Vec3f d(0.0f, -1.0f, 0.0f);

    REQUIRE_THAT(jtx::sphericalQuadArea(a, b, c, d), Catch::Matchers::WithinRel(jtx::PI_F * 2, T_EPS));
}