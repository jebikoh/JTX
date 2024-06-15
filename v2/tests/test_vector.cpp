/**
 * @file test_vector.cpp
 * This file contains tests for the Vec2, Vec3, and Vec4 classes
 * Only float versions are tested, which a few individual tests for integer versions
 */

#include "../src/util/vec2.hpp"
#include "../src/util/vec3.hpp"
#include "../src/util/vec4.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

static const float T_DEG_90 = 1.570796f;
static const float T_EPS = 0.0001f;


//region Vec3: Constructors
TEST_CASE("Vec3f default constructor", "[Vec3]") {
    jtx::Vec3f v;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 0.0f);
    REQUIRE(v.z == 0.0f);
}

TEST_CASE("Vec3f constructor", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
}

TEST_CASE("Vec3f copy constructor") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(v1);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}
//endregion

//region Vec3: Numerical validity
TEST_CASE("Vec3f valid", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    REQUIRE(v.valid());
}

// Vec3::valid() resulting in invalid can only be tested in release mode
#ifdef NDEBUG
TEST_CASE("Vec3f invalid", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, std::numeric_limits<float>::quiet_NaN());
    REQUIRE(!v.valid());
}
#endif
//endregion

//region Vec3: Unary oeprators
TEST_CASE("Vec3f operator- on positive values") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2 = -v1;
    REQUIRE(v2.x == -1.0f);
    REQUIRE(v2.y == -2.0f);
    REQUIRE(v2.z == -3.0f);
}

TEST_CASE("Vec3f operator- on negative values") {
    jtx::Vec3f v1(-1.0f, -2.0f, -3.0f);
    jtx::Vec3f v2 = -v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f operator+") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2 = +v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f ++ postfix operator") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2 = v++;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v.z == 4.0f);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f ++ prefix operator") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2 = ++v;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v.z == 4.0f);
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 3.0f);
    REQUIRE(v2.z == 4.0f);
}

TEST_CASE("Vec3f -- postfix operator") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2 = v--;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 1.0f);
    REQUIRE(v.z == 2.0f);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f -- prefix operator") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2 = --v;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 1.0f);
    REQUIRE(v.z == 2.0f);
    REQUIRE(v2.x == 0.0f);
    REQUIRE(v2.y == 1.0f);
    REQUIRE(v2.z == 2.0f);
}
//endregion

//region Vec3: Binary operators
TEST_CASE("Vec3f = operator", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    v2 = v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f == operator (equal)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(1.0f, 2.0f, 3.0f);
    REQUIRE(v1 == v2);
}

TEST_CASE("Vec3f == operator (unequal)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(1.0f, 2.0f, 4.0f);
    REQUIRE(!(v1 == v2));
}

TEST_CASE("Vec3f != operator (equal)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(1.0f, 2.0f, 3.0f);
    REQUIRE(!(v1 != v2));
}

TEST_CASE("Vec3f != operator (unequal)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(1.0f, 2.0f, 4.0f);
    REQUIRE(v1 != v2);
}

TEST_CASE("Vec3f + operator", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    jtx::Vec3f v3 = v1 + v2;
    REQUIRE(v3.x == 5.0f);
    REQUIRE(v3.y == 7.0f);
    REQUIRE(v3.z == 9.0f);
}

TEST_CASE("Vec3f - operator", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    jtx::Vec3f v3 = v1 - v2;
    REQUIRE(v3.x == -3.0f);
    REQUIRE(v3.y == -3.0f);
    REQUIRE(v3.z == -3.0f);
}

TEST_CASE("Vec3f * operator", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    jtx::Vec3f v3 = v1 * v2;
    REQUIRE(v3.x == 4.0f);
    REQUIRE(v3.y == 10.0f);
    REQUIRE(v3.z == 18.0f);
}

TEST_CASE("Vec3f * operator (scalar)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    float s = 2.0f;
    jtx::Vec3f v2 = v1 * s;
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 4.0f);
    REQUIRE(v2.z == 6.0f);
}

TEST_CASE("Vec3f * operator (LHS scalar)", "[Vec3]") {
    float s = 2.0f;
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2 = s * v1;
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 4.0f);
    REQUIRE(v2.z == 6.0f);
}

TEST_CASE("Vec3f / operator", "[Vec3]") {
    jtx::Vec3f v1(4.0f, 10.0f, 18.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    jtx::Vec3f v3 = v1 / v2;
    REQUIRE(v3.x == 1.0f);
    REQUIRE(v3.y == 2.0f);
    REQUIRE(v3.z == 3.0f);
}

TEST_CASE("Vec3f / operator (scalar)", "[Vec3]") {
    jtx::Vec3f v1(2.0f, 4.0f, 6.0f);
    float s = 2.0f;
    jtx::Vec3f v2 = v1 / s;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f / operator (LHS scalar)", "[Vec3]") {
    float s = 2.0f;
    jtx::Vec3f v1(2.0f, 4.0f, 6.0f);
    jtx::Vec3f v2 = s / v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 0.5f);
    REQUIRE(v2.z == 1.0f / 3.0f);
}
//endregion

//region Vec3: In-place operators
TEST_CASE("Vec3f += operator", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    v1 += v2;
    REQUIRE(v1.x == 5.0f);
    REQUIRE(v1.y == 7.0f);
    REQUIRE(v1.z == 9.0f);
}

TEST_CASE("Vec3f -= operator", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    v1 -= v2;
    REQUIRE(v1.x == -3.0f);
    REQUIRE(v1.y == -3.0f);
    REQUIRE(v1.z == -3.0f);
}

TEST_CASE("Vec3f *= operator", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    v1 *= v2;
    REQUIRE(v1.x == 4.0f);
    REQUIRE(v1.y == 10.0f);
    REQUIRE(v1.z == 18.0f);
}

TEST_CASE("Vec3f *= operator (scalar)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    float s = 2.0f;
    v1 *= s;
    REQUIRE(v1.x == 2.0f);
    REQUIRE(v1.y == 4.0f);
    REQUIRE(v1.z == 6.0f);
}

TEST_CASE("Vec3f /= operator", "[Vec3]") {
    jtx::Vec3f v1(4.0f, 10.0f, 18.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    v1 /= v2;
    REQUIRE(v1.x == 1.0f);
    REQUIRE(v1.y == 2.0f);
    REQUIRE(v1.z == 3.0f);
}

TEST_CASE("Vec3f /= operator (scalar)", "[Vec3]") {
    jtx::Vec3f v1(2.0f, 4.0f, 6.0f);
    float s = 2.0f;
    v1 /= s;
    REQUIRE(v1.x == 1.0f);
    REQUIRE(v1.y == 2.0f);
    REQUIRE(v1.z == 3.0f);
}
//endregion

//region Vec3: Member functions
TEST_CASE("Vec3f cross", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    jtx::Vec3f v3 = jtx::Vec3f::cross(v1, v2);
    REQUIRE(v3.x == -3.0f);
    REQUIRE(v3.y == 6.0f);
    REQUIRE(v3.z == -3.0f);
}

TEST_CASE("Vec3f dot", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    auto dot = v1.dot(v2);
    REQUIRE(dot == 32.0f);
}

TEST_CASE("Vec3f dot (with individual components)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    auto dot = v1.dot(4.0f, 5.0f, 6.0f);
    REQUIRE(dot == 32.0f);
}

TEST_CASE("Vec3f len", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    auto len = v.len();
    REQUIRE_THAT(len, Catch::Matchers::WithinRel(3.741657f, 0.0001f));
}

TEST_CASE("Vec3f normalize", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    v.normalize();
    REQUIRE_THAT(v.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
    REQUIRE_THAT(v.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
    REQUIRE_THAT(v.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

TEST_CASE("Vec3f normalize (static)", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    auto v2 = jtx::Vec3f::normalize(v);
    REQUIRE_THAT(v2.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
    REQUIRE_THAT(v2.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
    REQUIRE_THAT(v2.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

TEST_CASE("Vec3f abs", "[Vec3]") {
    jtx::Vec3f v(-1.0f, -2.0f, -3.0f);
    v.abs();
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
}

TEST_CASE("Vec3f abs (static)", "[Vec3]") {
    jtx::Vec3f v(-1.0f, -2.0f, -3.0f);
    auto v2 = jtx::Vec3f::abs(v);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f absdot", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(-4.0f, -5.0f, -6.0f);
    auto dot = v1.absdot(v2);
    REQUIRE(dot == 32.0f);
}

TEST_CASE("Vec3f absdot (static)", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(-4.0f, -5.0f, -6.0f);
    auto dot = jtx::Vec3f::absdot(v1, v2);
    REQUIRE(dot == 32.0f);

}

TEST_CASE("Vec3f ceil", "[Vec3]") {
    jtx::Vec3f v(1.1f, 2.2f, 3.3f);
    v.ceil();
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v.z == 4.0f);
}

TEST_CASE("Vec3f ceil (static)", "[Vec3]") {
    jtx::Vec3f v(1.1f, 2.2f, 3.3f);
    auto v2 = jtx::Vec3f::ceil(v);
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 3.0f);
    REQUIRE(v2.z == 4.0f);
}

TEST_CASE("Vec3f floor", "[Vec3]") {
    jtx::Vec3f v(1.1f, 2.2f, 3.3f);
    v.floor();
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
}

TEST_CASE("Vec3f floor (static)", "[Vec3]") {
    jtx::Vec3f v(1.1f, 2.2f, 3.3f);
    auto v2 = jtx::Vec3f::floor(v);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
}

TEST_CASE("Vec3f min", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    auto min = v.min();
    REQUIRE(min == 1.0f);
}

TEST_CASE("Vec3f min two vectors", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 1.0f, 2.0f);
    auto v3 = jtx::Vec3f::min(v1, v2);
    REQUIRE(v3.x == 1.0f);
    REQUIRE(v3.y == 1.0f);
    REQUIRE(v3.z == 2.0f);
}

TEST_CASE("Vec3f max", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    auto max = v.max();
    REQUIRE(max == 3.0f);
}

TEST_CASE("Vec3f max two vectors", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 1.0f, 2.0f);
    auto v3 = jtx::Vec3f::max(v1, v2);
    REQUIRE(v3.x == 4.0f);
    REQUIRE(v3.y == 2.0f);
    REQUIRE(v3.z == 3.0f);
}

TEST_CASE("Vec3f hprod", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    auto hprod = v.hprod();
    REQUIRE(hprod == 6.0f);
}

TEST_CASE("Vec3f hprod (static)", "[Vec3]") {
    jtx::Vec3f v(1.0f, 2.0f, 3.0f);
    auto hprod = jtx::Vec3f::hprod(v);
    REQUIRE(hprod == 6.0f);
}

TEST_CASE("Vec3f lerp", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    auto v3 = jtx::Vec3f::lerp(v1, v2, 0.5f);
    REQUIRE(v3.x == 2.5f);
    REQUIRE(v3.y == 3.5f);
    REQUIRE(v3.z == 4.5f);
}

TEST_CASE("Vec3f FMA", "[Vec3]") {
    jtx::Vec3f v1(1.0f, 2.0f, 3.0f);
    jtx::Vec3f v2(4.0f, 5.0f, 6.0f);
    jtx::Vec3f v3(7.0f, 8.0f, 9.0f);
    auto v4 = jtx::Vec3f::fma(v1, v2, v3);
    REQUIRE(v4.x == 11.0f);
    REQUIRE(v4.y == 18.0f);
    REQUIRE(v4.z == 27.0f);
}

TEST_CASE("Vec3f angle", "[Vec3]") {
    jtx::Vec3f up{0.0f, 1.0f, 0.0f};
    jtx::Vec3f forward{0.0f, 0.0f, 1.0f};
    auto theta = jtx::Vec3f::angle(up, forward);
    // 90 degrees
    REQUIRE_THAT(theta, Catch::Matchers::WithinRel(T_DEG_90, 0.0001f));
}

// TODO: this appears to be backwards?!
TEST_CASE("Vec3f Gram Schmidt") {
    jtx::Vec3f b{1.0f, 0.0f, 0.0f};
    jtx::Vec3f a{1.0f, 1.0f, 0.0f};
    auto c = jtx::Vec3f::gramSchmidt(a, b);
    REQUIRE(c.x == 0.0f);
    REQUIRE(c.y == 1.0f);
    REQUIRE(c.z == 0.0f);
}
//endregion

//region Vec3i Tests
TEST_CASE("Vec3i default constructor", "[Vec3]") {
    jtx::Vec3i v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
    REQUIRE(v.z == 0);
}

TEST_CASE("Vec3i valid", "[Vec3]") {
    jtx::Vec3i v(1, 2, 3);
    REQUIRE(v.valid());
}

TEST_CASE("Vec3i ceil") {
    jtx::Vec3i v(1, 2, 3);
    v.ceil();
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
    REQUIRE(v.z == 3);
}

TEST_CASE("Vec3i ceil (static)") {
    jtx::Vec3i v(1, 2, 3);
    auto v2 = jtx::Vec3i::ceil(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
    REQUIRE(v2.z == 3);
}

TEST_CASE("Vec3i floor") {
    jtx::Vec3i v(1, 2, 3);
    v.floor();
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
    REQUIRE(v.z == 3);
}

TEST_CASE("Vec3i floor (static)") {
    jtx::Vec3i v(1, 2, 3);
    auto v2 = jtx::Vec3i::floor(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
    REQUIRE(v2.z == 3);
}

TEST_CASE("Vec3i cross") {
    jtx::Vec3i v1(1, 2, 3);
    jtx::Vec3i v2(4, 5, 6);
    jtx::Vec3i v3 = jtx::Vec3i::cross(v1, v2);
    REQUIRE(v3.x == -3);
    REQUIRE(v3.y == 6);
    REQUIRE(v3.z == -3);
}

//endregion

//region Vec2: Constructors
TEST_CASE("Vec2f default constructor", "[Vec2]") {
    jtx::Vec2f v;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 0.0f);
}

TEST_CASE("Vec2f constructor", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
}

TEST_CASE("Vec2f copy constructor") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(v1);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}
//endregion

//region Vec2: Numerical validity
TEST_CASE("Vec2f valid", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    REQUIRE(v.valid());
}

// Vec2::valid() resulting in invalid can only be tested in release mode
#ifdef NDEBUG
TEST_CASE("Vec2f invalid", "[Vec2]") {
    jtx::Vec2f v(1.0f, std::numeric_limits<float>::quiet_NaN());
    REQUIRE(!v.valid());
}
#endif
//endregion

//region Vec2: Unary operators
TEST_CASE("Vec2f operator- on positive values") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2 = -v1;
    REQUIRE(v2.x == -1.0f);
    REQUIRE(v2.y == -2.0f);
}

TEST_CASE("Vec2f operator- on negative values") {
    jtx::Vec2f v1(-1.0f, -2.0f);
    jtx::Vec2f v2 = -v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f operator+") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2 = +v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f ++ postfix operator") {
    jtx::Vec2f v(1.0f, 2.0f);
    jtx::Vec2f v2 = v++;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f ++ prefix operator") {
    jtx::Vec2f v(1.0f, 2.0f);
    jtx::Vec2f v2 = ++v;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 3.0f);
}

TEST_CASE("Vec2f -- postfix operator") {
    jtx::Vec2f v(1.0f, 2.0f);
    jtx::Vec2f v2 = v--;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 1.0f);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f -- prefix operator") {
    jtx::Vec2f v(1.0f, 2.0f);
    jtx::Vec2f v2 = --v;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 1.0f);
    REQUIRE(v2.x == 0.0f);
    REQUIRE(v2.y == 1.0f);
}
//endregion

//region Vec2: Binary operators
TEST_CASE("Vec2f = operator", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    v2 = v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f == operator (equal)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(1.0f, 2.0f);
    REQUIRE(v1 == v2);
}

TEST_CASE("Vec2f == operator (unequal)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(1.0f, 3.0f);
    REQUIRE(!(v1 == v2));
}

TEST_CASE("Vec2f != operator (equal)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(1.0f, 2.0f);
    REQUIRE(!(v1 != v2));
}

TEST_CASE("Vec2f != operator (unequal)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(1.0f, 3.0f);
    REQUIRE(v1 != v2);
}

TEST_CASE("Vec2f + operator", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    jtx::Vec2f v3 = v1 + v2;
    REQUIRE(v3.x == 5.0f);
    REQUIRE(v3.y == 7.0f);
}

TEST_CASE("Vec2f - operator", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    jtx::Vec2f v3 = v1 - v2;
    REQUIRE(v3.x == -3.0f);
    REQUIRE(v3.y == -3.0f);
}

TEST_CASE("Vec2f * operator", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    jtx::Vec2f v3 = v1 * v2;
    REQUIRE(v3.x == 4.0f);
    REQUIRE(v3.y == 10.0f);
}

TEST_CASE("Vec2f * operator (scalar)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    float s = 2.0f;
    jtx::Vec2f v2 = v1 * s;
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 4.0f);
}

TEST_CASE("Vec2f * operator (LHS scalar") {
    float s = 2.0f;
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2 = s * v1;
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 4.0f);
}

TEST_CASE("Vec2f / operator", "[Vec2]") {
    jtx::Vec2f v1(4.0f, 10.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    jtx::Vec2f v3 = v1 / v2;
    REQUIRE(v3.x == 1.0f);
    REQUIRE(v3.y == 2.0f);
}

TEST_CASE("Vec2f / operator (scalar)", "[Vec2]") {
    jtx::Vec2f v1(2.0f, 4.0f);
    float s = 2.0f;
    jtx::Vec2f v2 = v1 / s;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f / operator (LHS scalar)", "[Vec2]") {
    float s = 2.0f;
    jtx::Vec2f v1(2.0f, 4.0f);
    jtx::Vec2f v2 = s / v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 0.5f);
}
//endregion

//region Vec2: In-place operators
TEST_CASE("Vec2f += operator", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    v1 += v2;
    REQUIRE(v1.x == 5.0f);
    REQUIRE(v1.y == 7.0f);
}

TEST_CASE("Vec2f -= operator", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    v1 -= v2;
    REQUIRE(v1.x == -3.0f);
    REQUIRE(v1.y == -3.0f);
}

TEST_CASE("Vec2f *= operator", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    v1 *= v2;
    REQUIRE(v1.x == 4.0f);
    REQUIRE(v1.y == 10.0f);
}

TEST_CASE("Vec2f *= operator (scalar)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    float s = 2.0f;
    v1 *= s;
    REQUIRE(v1.x == 2.0f);
    REQUIRE(v1.y == 4.0f);
}

TEST_CASE("Vec2f /= operator", "[Vec2]") {
    jtx::Vec2f v1(4.0f, 10.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    v1 /= v2;
    REQUIRE(v1.x == 1.0f);
    REQUIRE(v1.y == 2.0f);
}

TEST_CASE("Vec2f /= operator (scalar)", "[Vec2]") {
    jtx::Vec2f v1(2.0f, 4.0f);
    float s = 2.0f;
    v1 /= s;
    REQUIRE(v1.x == 1.0f);
    REQUIRE(v1.y == 2.0f);
}
//endregion

//region Vec2: Member functions
TEST_CASE("Vec2f dot", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    auto dot = v1.dot(v2);
    REQUIRE(dot == 14.0f);
}

TEST_CASE("Vec2f dot (with individual components)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    auto dot = v1.dot(4.0f, 5.0f);
    REQUIRE(dot == 14.0f);
}

TEST_CASE("Vec2f len", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    auto len = v.len();
    REQUIRE_THAT(len, Catch::Matchers::WithinRel(2.236067f, 0.0001f));
}

TEST_CASE("Vec2f normalize", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    v.normalize();
    REQUIRE_THAT(v.x, Catch::Matchers::WithinRel(0.447214f, 0.0001f));
    REQUIRE_THAT(v.y, Catch::Matchers::WithinRel(0.894428f, 0.0001f));
}

TEST_CASE("Vec2f normalize (static)", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    auto v2 = jtx::Vec2f::normalize(v);
    REQUIRE_THAT(v2.x, Catch::Matchers::WithinRel(0.447214f, 0.0001f));
    REQUIRE_THAT(v2.y, Catch::Matchers::WithinRel(0.894428f, 0.0001f));
}

TEST_CASE("Vec2f abs", "[Vec2]") {
    jtx::Vec2f v(-1.0f, -2.0f);
    v.abs();
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
}

TEST_CASE("Vec2f abs (static)", "[Vec2]") {
    jtx::Vec2f v(-1.0f, -2.0f);
    auto v2 = jtx::Vec2f::abs(v);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f absdot", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(-4.0f, -5.0f);
    auto dot = v1.absdot(v2);
    REQUIRE(dot == 14.0f);
}

TEST_CASE("Vec2f absdot (static)", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(-4.0f, -5.0f);
    auto dot = jtx::Vec2f::absdot(v1, v2);
    REQUIRE(dot == 14.0f);
}

TEST_CASE("Vec2f ceil", "[Vec2]") {
    jtx::Vec2f v(1.1f, 2.2f);
    v.ceil();
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
}

TEST_CASE("Vec2f ceil (static)", "[Vec2]") {
    jtx::Vec2f v(1.1f, 2.2f);
    auto v2 = jtx::Vec2f::ceil(v);
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 3.0f);
}

TEST_CASE("Vec2f floor", "[Vec2]") {
    jtx::Vec2f v(1.1f, 2.2f);
    v.floor();
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
}

TEST_CASE("Vec2f floor (static)", "[Vec2]") {
    jtx::Vec2f v(1.1f, 2.2f);
    auto v2 = jtx::Vec2f::floor(v);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
}

TEST_CASE("Vec2f min", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    auto min = v.min();
    REQUIRE(min == 1.0f);
}

TEST_CASE("Vec2f min two vectors", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 1.0f);
    auto v3 = jtx::Vec2f::min(v1, v2);
    REQUIRE(v3.x == 1.0f);
    REQUIRE(v3.y == 1.0f);
}

TEST_CASE("Vec2f max", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    auto max = v.max();
    REQUIRE(max == 2.0f);
}

TEST_CASE("Vec2f max two vectors", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 1.0f);
    auto v3 = jtx::Vec2f::max(v1, v2);
    REQUIRE(v3.x == 4.0f);
    REQUIRE(v3.y == 2.0f);
}

TEST_CASE("Vec2f hprod", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    auto hprod = v.hprod();
    REQUIRE(hprod == 2.0f);
}

TEST_CASE("Vec2f hprod (static)", "[Vec2]") {
    jtx::Vec2f v(1.0f, 2.0f);
    auto hprod = jtx::Vec2f::hprod(v);
    REQUIRE(hprod == 2.0f);
}

TEST_CASE("Vec2f lerp", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    auto v3 = jtx::Vec2f::lerp(v1, v2, 0.5f);
    REQUIRE(v3.x == 2.5f);
    REQUIRE(v3.y == 3.5f);
}

TEST_CASE("Vec2f FMA", "[Vec2]") {
    jtx::Vec2f v1(1.0f, 2.0f);
    jtx::Vec2f v2(4.0f, 5.0f);
    jtx::Vec2f v3(7.0f, 8.0f);
    auto v4 = jtx::Vec2f::fma(v1, v2, v3);
    REQUIRE(v4.x == 11.0f);
    REQUIRE(v4.y == 18.0f);
}

TEST_CASE("Vec2f angle", "[Vec2]") {
    jtx::Vec2f up{0.0f, 1.0f};
    jtx::Vec2f right{1.0f, 0.0f};
    auto theta = jtx::Vec2f::angle(up, right);
    // 90 degrees
    REQUIRE_THAT(theta, Catch::Matchers::WithinRel(T_DEG_90, 0.0001f));
}

// TODO: this appears to be backwards?!
TEST_CASE("Vec2f Gram Schmidt", "[Vec2]") {
    jtx::Vec2f b{1.0f, 0.0f};
    jtx::Vec2f a{1.0f, 1.0f};
    auto c = jtx::Vec2f::gramSchmidt(a, b);
    REQUIRE(c.x == 0.0f);
    REQUIRE(c.y == 1.0f);
}
//endregion

//region Vec2i Tests
TEST_CASE("Vec2i default constructor", "[Vec2]") {
    jtx::Vec2i v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
}

TEST_CASE("Vec2i valid", "[Vec2]") {
    jtx::Vec2i v(1, 2);
    REQUIRE(v.valid());
}

TEST_CASE("Vec2i ceil") {
    jtx::Vec2i v(1, 2);
    v.ceil();
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
}

TEST_CASE("Vec2i ceil (static)") {
    jtx::Vec2i v(1, 2);
    auto v2 = jtx::Vec2i::ceil(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
}

TEST_CASE("Vec2i floor") {
    jtx::Vec2i v(1, 2);
    v.floor();
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
}

TEST_CASE("Vec2i floor (static)") {
    jtx::Vec2i v(1, 2);
    auto v2 = jtx::Vec2i::floor(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
}

//endregion

//region Vec4: Constructors
TEST_CASE("Vec4f default constructor", "[Vec4]") {
    jtx::Vec4f v;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 0.0f);
    REQUIRE(v.z == 0.0f);
    REQUIRE(v.w == 0.0f);
}

TEST_CASE("Vec4f constructor", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
    REQUIRE(v.w == 4.0f);
}

TEST_CASE("Vec4f copy constructor") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(v1);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}
//endregion

//region Vec4: Numerical validity
TEST_CASE("Vec4f valid", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    REQUIRE(v.valid());
}

// Vec4::valid() resulting in invalid can only be tested in release mode
#ifdef NDEBUG
TEST_CASE("Vec4f invalid", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 4.0f, std::numeric_limits<float>::quiet_NaN());
    REQUIRE(!v.valid());
}
#endif
//endregion

//region Vec4: Unary operators
TEST_CASE("Vec4f operator- on positive values") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2 = -v1;
    REQUIRE(v2.x == -1.0f);
    REQUIRE(v2.y == -2.0f);
    REQUIRE(v2.z == -3.0f);
    REQUIRE(v2.w == -4.0f);
}

TEST_CASE("Vec4f operator- on negative values") {
    jtx::Vec4f v1(-1.0f, -2.0f, -3.0f, -4.0f);
    jtx::Vec4f v2 = -v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}

TEST_CASE("Vec4f operator+") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2 = +v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}

TEST_CASE("Vec4f ++ postfix operator") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2 = v++;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v.z == 4.0f);
    REQUIRE(v.w == 5.0f);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}

TEST_CASE("Vec4f ++ prefix operator") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2 = ++v;
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v.z == 4.0f);
    REQUIRE(v.w == 5.0f);
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 3.0f);
    REQUIRE(v2.z == 4.0f);
    REQUIRE(v2.w == 5.0f);
}

TEST_CASE("Vec4f -- postfix operator") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2 = v--;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 1.0f);
    REQUIRE(v.z == 2.0f);
    REQUIRE(v.w == 3.0f);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}

TEST_CASE("Vec4f -- prefix operator") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2 = --v;
    REQUIRE(v.x == 0.0f);
    REQUIRE(v.y == 1.0f);
    REQUIRE(v.z == 2.0f);
    REQUIRE(v.w == 3.0f);
    REQUIRE(v2.x == 0.0f);
    REQUIRE(v2.y == 1.0f);
    REQUIRE(v2.z == 2.0f);
    REQUIRE(v2.w == 3.0f);
}
//endregion

//region Vec4: Binary operators
TEST_CASE("Vec4f = operator", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 4.0f);
    v2 = v1;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}

TEST_CASE("Vec4f == operator (equal)", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(1.0f, 2.0f, 3.0f, 4.0f);
    REQUIRE(v1 == v2);
}

TEST_CASE("Vec4f == operator (unequal)", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(1.0f, 2.0f, 4.0f, 4.0f);
    REQUIRE(!(v1 == v2));
}

TEST_CASE("Vec4f != operator (equal)", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(1.0f, 2.0f, 3.0f, 4.0f);
    REQUIRE(!(v1 != v2));
}

TEST_CASE("Vec4f != operator (unequal)", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(1.0f, 2.0f, 4.0f, 4.0f);
    REQUIRE(v1 != v2);
}

TEST_CASE("Vec4f + operator", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    jtx::Vec4f v3 = v1 + v2;
    REQUIRE(v3.x == 5.0f);
    REQUIRE(v3.y == 7.0f);
    REQUIRE(v3.z == 9.0f);
    REQUIRE(v3.w == 11.0f);
}

TEST_CASE("Vec4f - operator", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    jtx::Vec4f v3 = v1 - v2;
    REQUIRE(v3.x == -3.0f);
    REQUIRE(v3.y == -3.0f);
    REQUIRE(v3.z == -3.0f);
    REQUIRE(v3.w == -3.0f);
}

TEST_CASE("Vec4f * operator", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    jtx::Vec4f v3 = v1 * v2;
    REQUIRE(v3.x == 4.0f);
    REQUIRE(v3.y == 10.0f);
    REQUIRE(v3.z == 18.0f);
    REQUIRE(v3.w == 28.0f);
}

TEST_CASE("Vec4f * operator (scalar)", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    float s = 2.0f;
    jtx::Vec4f v2 = v1 * s;
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 4.0f);
    REQUIRE(v2.z == 6.0f);
    REQUIRE(v2.w == 8.0f);
}

TEST_CASE("Vec4f / operator", "[Vec4]") {
    jtx::Vec4f v1(4.0f, 10.0f, 18.0f, 28.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    jtx::Vec4f v3 = v1 / v2;
    REQUIRE(v3.x == 1.0f);
    REQUIRE(v3.y == 2.0f);
    REQUIRE(v3.z == 3.0f);
    REQUIRE(v3.w == 4.0f);
}

TEST_CASE("Vec4f / operator (scalar)", "[Vec4]") {
    jtx::Vec4f v1(2.0f, 4.0f, 6.0f, 8.0f);
    float s = 2.0f;
    jtx::Vec4f v2 = v1 / s;
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}
//endregion

//region Vec4: In-place operators
TEST_CASE("Vec4f += operator", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    v1 += v2;
    REQUIRE(v1.x == 5.0f);
    REQUIRE(v1.y == 7.0f);
    REQUIRE(v1.z == 9.0f);
    REQUIRE(v1.w == 11.0f);
}

TEST_CASE("Vec4f -= operator", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    v1 -= v2;
    REQUIRE(v1.x == -3.0f);
    REQUIRE(v1.y == -3.0f);
    REQUIRE(v1.z == -3.0f);
    REQUIRE(v1.w == -3.0f);
}

TEST_CASE("Vec4f *= operator", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    v1 *= v2;
    REQUIRE(v1.x == 4.0f);
    REQUIRE(v1.y == 10.0f);
    REQUIRE(v1.z == 18.0f);
    REQUIRE(v1.w == 28.0f);
}

TEST_CASE("Vec4f *= operator (scalar)", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    float s = 2.0f;
    v1 *= s;
    REQUIRE(v1.x == 2.0f);
    REQUIRE(v1.y == 4.0f);
    REQUIRE(v1.z == 6.0f);
    REQUIRE(v1.w == 8.0f);
}

TEST_CASE("Vec4f /= operator", "[Vec4]") {
    jtx::Vec4f v1(4.0f, 10.0f, 18.0f, 28.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    v1 /= v2;
    REQUIRE(v1.x == 1.0f);
    REQUIRE(v1.y == 2.0f);
    REQUIRE(v1.z == 3.0f);
    REQUIRE(v1.w == 4.0f);
}

TEST_CASE("Vec4f /= operator (scalar)", "[Vec4]") {
    jtx::Vec4f v1(2.0f, 4.0f, 6.0f, 8.0f);
    float s = 2.0f;
    v1 /= s;
    REQUIRE(v1.x == 1.0f);
    REQUIRE(v1.y == 2.0f);
    REQUIRE(v1.z == 3.0f);
    REQUIRE(v1.w == 4.0f);
}
//endregion

//region Vec4: Member functions

TEST_CASE("Vec4f dot", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    auto dot = v1.dot(v2);
    REQUIRE(dot == 60.0f);
}

TEST_CASE("Vec4f dot (with individual components)", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    auto dot = v1.dot(4.0f, 5.0f, 6.0f, 7.0f);
    REQUIRE(dot == 60.0f);
}

TEST_CASE("Vec4f len", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    auto len = v.len();
    REQUIRE_THAT(len, Catch::Matchers::WithinRel(5.477225f, 0.0001f));
}

TEST_CASE("Vec4f normalize", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    v.normalize();
    REQUIRE_THAT(v.x, Catch::Matchers::WithinRel(0.182574f, 0.0001f));
    REQUIRE_THAT(v.y, Catch::Matchers::WithinRel(0.365148f, 0.0001f));
    REQUIRE_THAT(v.z, Catch::Matchers::WithinRel(0.547722f, 0.0001f));
    REQUIRE_THAT(v.w, Catch::Matchers::WithinRel(0.730296f, 0.0001f));
}

TEST_CASE("Vec4f normalize (static)", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    auto v2 = jtx::Vec4f::normalize(v);
    REQUIRE_THAT(v2.x, Catch::Matchers::WithinRel(0.182574f, 0.0001f));
    REQUIRE_THAT(v2.y, Catch::Matchers::WithinRel(0.365148f, 0.0001f));
    REQUIRE_THAT(v2.z, Catch::Matchers::WithinRel(0.547722f, 0.0001f));
    REQUIRE_THAT(v2.w, Catch::Matchers::WithinRel(0.730296f, 0.0001f));
}

TEST_CASE("Vec4f abs", "[Vec4]") {
    jtx::Vec4f v(-1.0f, -2.0f, -3.0f, -4.0f);
    v.abs();
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
    REQUIRE(v.w == 4.0f);
}

TEST_CASE("Vec4f abs (static)", "[Vec4]") {
    jtx::Vec4f v(-1.0f, -2.0f, -3.0f, -4.0f);
    auto v2 = jtx::Vec4f::abs(v);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}

TEST_CASE("Vec4f ceil", "[Vec4]") {
    jtx::Vec4f v(1.1f, 2.2f, 3.3f, 4.4f);
    v.ceil();
    REQUIRE(v.x == 2.0f);
    REQUIRE(v.y == 3.0f);
    REQUIRE(v.z == 4.0f);
    REQUIRE(v.w == 5.0f);
}

TEST_CASE("Vec4f ceil (static)", "[Vec4]") {
    jtx::Vec4f v(1.1f, 2.2f, 3.3f, 4.4f);
    auto v2 = jtx::Vec4f::ceil(v);
    REQUIRE(v2.x == 2.0f);
    REQUIRE(v2.y == 3.0f);
    REQUIRE(v2.z == 4.0f);
    REQUIRE(v2.w == 5.0f);
}

TEST_CASE("Vec4f floor", "[Vec4]") {
    jtx::Vec4f v(1.1f, 2.2f, 3.3f, 4.4f);
    v.floor();
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
    REQUIRE(v.w == 4.0f);
}

TEST_CASE("Vec4f floor (static)", "[Vec4]") {
    jtx::Vec4f v(1.1f, 2.2f, 3.3f, 4.4f);
    auto v2 = jtx::Vec4f::floor(v);
    REQUIRE(v2.x == 1.0f);
    REQUIRE(v2.y == 2.0f);
    REQUIRE(v2.z == 3.0f);
    REQUIRE(v2.w == 4.0f);
}

TEST_CASE("Vec4f min", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    auto min = v.min();
    REQUIRE(min == 1.0f);
}

TEST_CASE("Vec4f min two vectors", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 1.0f, 2.0f, 5.0f);
    auto v3 = jtx::Vec4f::min(v1, v2);
    REQUIRE(v3.x == 1.0f);
    REQUIRE(v3.y == 1.0f);
    REQUIRE(v3.z == 2.0f);
    REQUIRE(v3.w == 4.0f);
}

TEST_CASE("Vec4f max", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    auto max = v.max();
    REQUIRE(max == 4.0f);
}

TEST_CASE("Vec4f max two vectors", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 1.0f, 2.0f, 5.0f);
    auto v3 = jtx::Vec4f::max(v1, v2);
    REQUIRE(v3.x == 4.0f);
    REQUIRE(v3.y == 2.0f);
    REQUIRE(v3.z == 3.0f);
    REQUIRE(v3.w == 5.0f);
}

TEST_CASE("Vec4f hprod", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    auto hprod = v.hprod();
    REQUIRE(hprod == 24.0f);
}

TEST_CASE("Vec4f hprod (static)", "[Vec4]") {
    jtx::Vec4f v(1.0f, 2.0f, 3.0f, 4.0f);
    auto hprod = jtx::Vec4f::hprod(v);
    REQUIRE(hprod == 24.0f);
}

TEST_CASE("Vec4f lerp", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    auto v3 = jtx::Vec4f::lerp(v1, v2, 0.5f);
    REQUIRE(v3.x == 2.5f);
    REQUIRE(v3.y == 3.5f);
    REQUIRE(v3.z == 4.5f);
    REQUIRE(v3.w == 5.5f);
}

TEST_CASE("Vec4f FMA", "[Vec4]") {
    jtx::Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    jtx::Vec4f v2(4.0f, 5.0f, 6.0f, 7.0f);
    jtx::Vec4f v3(7.0f, 8.0f, 9.0f, 10.0f);
    auto v4 = jtx::Vec4f::fma(v1, v2, v3);
    REQUIRE(v4.x == 11.0f);
    REQUIRE(v4.y == 18.0f);
    REQUIRE(v4.z == 27.0f);
    REQUIRE(v4.w == 38.0f);
}
//endregion

//region Vec4i Tests
TEST_CASE("Vec4i default constructor", "[Vec4]") {
    jtx::Vec4i v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
    REQUIRE(v.z == 0);
    REQUIRE(v.w == 0);
}

TEST_CASE("Vec4i valid", "[Vec4]") {
    jtx::Vec4i v(1, 2, 3, 4);
    REQUIRE(v.valid());
}

TEST_CASE("Vec4i ceil") {
    jtx::Vec4i v(1, 2, 3, 4);
    v.ceil();
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
    REQUIRE(v.z == 3);
    REQUIRE(v.w == 4);
}

TEST_CASE("Vec4i ceil (static)") {
    jtx::Vec4i v(1, 2, 3, 4);
    auto v2 = jtx::Vec4i::ceil(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
    REQUIRE(v2.z == 3);
    REQUIRE(v2.w == 4);
}

TEST_CASE("Vec4i floor") {
    jtx::Vec4i v(1, 2, 3, 4);
    v.floor();
    REQUIRE(v.x == 1);
    REQUIRE(v.y == 2);
    REQUIRE(v.z == 3);
    REQUIRE(v.w == 4);
}

TEST_CASE("Vec4i floor (static)") {
    jtx::Vec4i v(1, 2, 3, 4);
    auto v2 = jtx::Vec4i::floor(v);
    REQUIRE(v2.x == 1);
    REQUIRE(v2.y == 2);
    REQUIRE(v2.z == 3);
    REQUIRE(v2.w == 4);
}

//endregion