#include <jtxlib/math/vec3.hpp>
#include <jtxlib/math/quaternion.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "./tconstants.h"

TEST_CASE("Quaternion default constructor returns identity", "[Quaternion]") {
    jtx::Quaternion q{};
    REQUIRE(q.w == 1.0f);
    REQUIRE(q.v.x == 0.0f);
    REQUIRE(q.v.y == 0.0f);
    REQUIRE(q.v.z == 0.0f);
}

TEST_CASE("Quaternion non-default constructors", "[Quaternion]") {
    SECTION("Using w and Vec3f v") {
        jtx::Quaternion q{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
        REQUIRE(q.w == 1.0f);
        REQUIRE(q.v.x == 1.0f);
        REQUIRE(q.v.y == 2.0f);
        REQUIRE(q.v.z == 3.0f);
    }

    SECTION("Using w, x, y, and z", "[Quaternion]") {
        jtx::Quaternion q{1.0f, 1.0f, 2.0f, 3.0f};
        REQUIRE(q.w == 1.0f);
        REQUIRE(q.v.x == 1.0f);
        REQUIRE(q.v.y == 2.0f);
        REQUIRE(q.v.z == 3.0f);
    }
}

TEST_CASE("Quaternion pure static constructor", "[Quaternion]") {
    jtx::Quaternion q = jtx::Quaternion::pure(jtx::Vec3f{1.0f, 2.0f, 3.0f});
    REQUIRE(q.w == 0.0f);
    REQUIRE(q.v.x == 1.0f);
    REQUIRE(q.v.y == 2.0f);
    REQUIRE(q.v.z == 3.0f);
}

TEST_CASE("Quaternion real static constructor", "[Quaternion]") {
    jtx::Quaternion q = jtx::Quaternion::real(1.0f);
    REQUIRE(q.w == 1.0f);
    REQUIRE(q.v.x == 0.0f);
    REQUIRE(q.v.y == 0.0f);
    REQUIRE(q.v.z == 0.0f);
}

TEST_CASE("Quaternion addition operator", "[Quaternion]") {
    jtx::Quaternion q1{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    jtx::Quaternion q2{2.0f, jtx::Vec3f{4.0f, 5.0f, 6.0f}};
    jtx::Quaternion q3 = q1 + q2;
    REQUIRE(q3.w == 3.0f);
    REQUIRE(q3.v.x == 5.0f);
    REQUIRE(q3.v.y == 7.0f);
    REQUIRE(q3.v.z == 9.0f);
}

TEST_CASE("Quaternion subtraction operator", "[Quaternion]") {
    jtx::Quaternion q1{2.0f, jtx::Vec3f{4.0f, 5.0f, 6.0f}};
    jtx::Quaternion q2{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    jtx::Quaternion q3 = q1 - q2;
    REQUIRE(q3.w == 1.0f);
    REQUIRE(q3.v.x == 3.0f);
    REQUIRE(q3.v.y == 3.0f);
    REQUIRE(q3.v.z == 3.0f);
}

TEST_CASE("Quaternion negation operator", "[Quaternion]") {
    jtx::Quaternion q{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    jtx::Quaternion q_neg = -q;
    REQUIRE(q_neg.w == -1.0f);
    REQUIRE(q_neg.v.x == -1.0f);
    REQUIRE(q_neg.v.y == -2.0f);
    REQUIRE(q_neg.v.z == -3.0f);
}

TEST_CASE("Quaternion multiplication operator", "[Quaternion]") {
    jtx::Quaternion q1{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    jtx::Quaternion q2{2.0f, jtx::Vec3f{4.0f, 5.0f, 6.0f}};
    jtx::Quaternion q3 = q1 * q2;
    REQUIRE(q3.w == -30.0f);
    REQUIRE(q3.v.x == 3.0f);
    REQUIRE(q3.v.y == 15.0f);
    REQUIRE(q3.v.z == 9.0f);
}

TEST_CASE("Quaternion scalar multiplication operator", "[Quaternion]") {
    jtx::Quaternion q{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    jtx::Quaternion q_scaled = q * 2.0f;
    REQUIRE(q_scaled.w == 2.0f);
    REQUIRE(q_scaled.v.x == 2.0f);
    REQUIRE(q_scaled.v.y == 4.0f);
    REQUIRE(q_scaled.v.z == 6.0f);
}

TEST_CASE("Quaternion scalar division operator", "[Quaternion]") {
    jtx::Quaternion q{2.0f, jtx::Vec3f{2.0f, 4.0f, 6.0f}};
    jtx::Quaternion q_divided = q / 2.0f;
    REQUIRE(q_divided.w == 1.0f);
    REQUIRE(q_divided.v.x == 1.0f);
    REQUIRE(q_divided.v.y == 2.0f);
    REQUIRE(q_divided.v.z == 3.0f);
}

TEST_CASE("Quaternion addition assignment operator", "[Quaternion]") {
    jtx::Quaternion q1{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    jtx::Quaternion q2{2.0f, jtx::Vec3f{4.0f, 5.0f, 6.0f}};
    q1 += q2;
    REQUIRE(q1.w == 3.0f);
    REQUIRE(q1.v.x == 5.0f);
    REQUIRE(q1.v.y == 7.0f);
    REQUIRE(q1.v.z == 9.0f);
}

TEST_CASE("Quaternion subtraction assignment operator", "[Quaternion]") {
    jtx::Quaternion q1{2.0f, jtx::Vec3f{4.0f, 5.0f, 6.0f}};
    jtx::Quaternion q2{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    q1 -= q2;
    REQUIRE(q1.w == 1.0f);
    REQUIRE(q1.v.x == 3.0f);
    REQUIRE(q1.v.y == 3.0f);
    REQUIRE(q1.v.z == 3.0f);
}

TEST_CASE("Quaternion multiplication assignment operator", "[Quaternion]") {
    jtx::Quaternion q1{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    jtx::Quaternion q2{2.0f, jtx::Vec3f{4.0f, 5.0f, 6.0f}};
    q1 *= q2;
    REQUIRE(q1.w == -30.0f);
    REQUIRE(q1.v.x == 3.0f);
    REQUIRE(q1.v.y == 15.0f);
    REQUIRE(q1.v.z == 9.0f);
}

TEST_CASE("Quaternion scalar multiplication assignment operator", "[Quaternion]") {
    jtx::Quaternion q{1.0f, jtx::Vec3f{1.0f, 2.0f, 3.0f}};
    q *= 2.0f;
    REQUIRE(q.w == 2.0f);
    REQUIRE(q.v.x == 2.0f);
    REQUIRE(q.v.y == 4.0f);
    REQUIRE(q.v.z == 6.0f);
}

TEST_CASE("Quaternion scalar division assignment operator", "[Quaternion]") {
    jtx::Quaternion q{2.0f, jtx::Vec3f{2.0f, 4.0f, 6.0f}};
    q /= 2.0f;
    REQUIRE(q.w == 1.0f);
    REQUIRE(q.v.x == 1.0f);
    REQUIRE(q.v.y == 2.0f);
    REQUIRE(q.v.z == 3.0f);
}