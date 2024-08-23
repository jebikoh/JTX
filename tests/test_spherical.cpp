#include <jtxlib/math/spherical.hpp>
#include "./tconstants.h"
#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace jtx;

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

//region Octahedral Encoding
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
TEST_CASE("Equal Area Square To Sphere", "[Spherical]") {
    SECTION("Center") {
        Vec3f v = equalAreaSquareToSphere(Vec2f(0.5f, 0.5f));
        REQUIRE(v.equals(Vec3f(0, 0, 1), T_EPS));
    }

    SECTION("Top") {
        Vec3f v = equalAreaSquareToSphere(Vec2f(0.5f, 1.0f));
        REQUIRE(v.equals(Vec3f(0, 1, 0), T_EPS));
    }

    SECTION("Bottom") {
        Vec3f v = equalAreaSquareToSphere(Vec2f(0.5f, 0.0f));
        REQUIRE(v.equals(Vec3f(0, -1, 0), T_EPS));
    }

    SECTION("Right") {
        Vec3f v = equalAreaSquareToSphere(Vec2f(1.0f, 0.5f));
        REQUIRE(v.equals(Vec3f(1, 0, 0), T_EPS));
    }
}

TEST_CASE("Equal Area Sphere to Square", "[Spherical]") {
    const float eps = 1e-3;
    SECTION("Center") {
        Vec2f v = equalAreaSphereToSquare(Vec3f(0, 0, 1));
        REQUIRE_THAT(v.x, Catch::Matchers::WithinRel(0.5f, eps));
        REQUIRE_THAT(v.y, Catch::Matchers::WithinRel(0.5f, eps));
    }

    SECTION("Top") {
        Vec2f v = equalAreaSphereToSquare(Vec3f(0, 1, 0));
        REQUIRE(v.equals(Vec2f(0.5f, 1.0f), T_EPS));
    }

    SECTION("Bottom") {
        Vec2f v = equalAreaSphereToSquare(Vec3f(0, -1, 0));
        REQUIRE(v.equals(Vec2f(0.5f, 0.0f), T_EPS));
    }

    SECTION("Right") {
        Vec2f v = equalAreaSphereToSquare(Vec3f(1, 0, 0));
        REQUIRE(v.equals(Vec2f(1.0f, 0.5f), T_EPS));
    }
}

TEST_CASE("Point to square to sphere to square preserves point", "[Spherical]") {
    const float eps = 1e-3;
    Point2f p(0.25f, 0.75f);
    Vec3f v = equalAreaSquareToSphere(p);
    Point2f p2 = equalAreaSphereToSquare(v);
    REQUIRE(p.equals(p2, eps));
}

TEST_CASE("Wrap equal area sphere", "[Spherical]") {
    SECTION("Top and right") {
        Point2f p(1.1f, 1.1f);
        Point2f result = wrapEqualAreaSquare(p);
        std::cout << toString(result) << std::endl;
        REQUIRE(result.equals(Point2f(0.1f, 0.1f), T_EPS));
    }

    SECTION("Bottom and left") {
        Point2f p(-0.1f, -0.1f);
        Point2f result = wrapEqualAreaSquare(p);
        REQUIRE(result.equals(Point2f(0.9f, 0.9f), T_EPS));
    }
}
//endregion

//region Direction Cone
TEST_CASE("DirectionCone default constructor creates an empty cone", "[DirectionCone]") {
    jtx::DirectionCone cone;
    REQUIRE(cone.isEmpty());
}

TEST_CASE("DirectionCone entireSphere creates a cone covering the entire sphere", "[DirectionCone]") {
    auto cone = jtx::DirectionCone::entireSphere();
    REQUIRE(cone.dir == jtx::Vec3f(0, 0, 0));
    REQUIRE(cone.cosTheta == -1);

    Vec3f v = Vec3f(1, 0, 0);
    REQUIRE(jtx::inside(cone, v));
}

TEST_CASE("inside() returns true for vectors inside the cone", "[DirectionCone]") {
    jtx::Vec3f dir(0.0f, 0.0f, 1.0f);
    jtx::DirectionCone cone(dir, 0.5f);
    jtx::Vec3f v(0.0f, 0.5f, 0.5f);
    REQUIRE(jtx::inside(cone, v));
}

TEST_CASE("inside() returns false for vectors outside the cone", "[DirectionCone]") {
    jtx::Vec3f dir(0.0f, 0.0f, 1.0f);
    jtx::DirectionCone cone(dir, 0.5f);
    jtx::Vec3f v(1.0f, 0.0f, 0.0f);
    REQUIRE_FALSE(jtx::inside(cone, v));
}

TEST_CASE("boundSubtendedDirection returns entire sphere if point is inside bbox", "[DirectionCone]") {
    jtx::BBox3f bounds(jtx::Point3f(-1, -1, -1), jtx::Point3f(1, 1, 1));
    jtx::Vec3f p(0.0f, 0.0f, 0.0f);
    auto cone = jtx::boundSubtendedDirection(bounds, p);
    REQUIRE(cone.equals(jtx::DirectionCone::entireSphere(), T_EPS));
}

TEST_CASE("boundSubtendedDirection returns correct cone", "[DirectionCone]") {
    jtx::BBox3f bounds(jtx::Point3f(-1, -1, -1), jtx::Point3f(1, 1, 1));
    jtx::Vec3f p(3.0f, 0.0f, 0.0f);
    auto cone = jtx::boundSubtendedDirection(bounds, p);
    REQUIRE(cone.dir.equals(jtx::Vec3f(-1, 0, 0), T_EPS));

    // Check if the bound maxes are included--the cone does not intersect the
    // equivalent bounding sphere at the maxes.
    REQUIRE(jtx::inside(cone, jtx::Point3f(-1, -1, -1) - p));
    REQUIRE(jtx::inside(cone, jtx::Point3f(1, 1, 1) - p));
}

TEST_CASE("merge returns the larger cone when one cone is inside the other", "[DirectionCone]") {
    float theta1 = 0.5f;
    float theta2 = 0.8f;
    jtx::Vec3f dir1(0.0f, 0.0f, 1.0f);
    jtx::DirectionCone cone1(dir1, jtx::cos(theta1));
    jtx::Vec3f dir2(0.0f, 0.0f, 1.0f);
    jtx::DirectionCone cone2(dir2, jtx::cos(theta2));
    auto mergedCone = jtx::merge(cone1, cone2);
    REQUIRE(mergedCone.equals(cone2, T_EPS));
}

TEST_CASE("merge returns a new cone when cones are not inside each other", "[DirectionCone]") {
    jtx::Vec3f dir1(1.0f, 0.0f, 0.0f);
    jtx::DirectionCone cone1(dir1, 0.5f);
    jtx::Vec3f dir2(0.0f, 1.0f, 0.0f);
    jtx::DirectionCone cone2(dir2, 0.5f);
    auto mergedCone = jtx::merge(cone1, cone2);
    REQUIRE(mergedCone.dir.equals(jtx::Vec3f(1, 1, 0).normalize(), T_EPS));
    REQUIRE(inside(mergedCone, jtx::Vec3f(1, 0, 0)));
    REQUIRE(inside(mergedCone, jtx::Vec3f(0, 1, 0)));
}
//endregion