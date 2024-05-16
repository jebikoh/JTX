#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "JTX/util/util.hpp"

TEST_CASE("Vec3 default constructor is zero vector", "[vec3]") {
    JTX::Util::Vec3 a{};

    REQUIRE(a.x == 0.0f);
    REQUIRE(a.y == 0.0f);
    REQUIRE(a.z == 0.0f);
}

TEST_CASE("Vec4 default constructor is zero vector", "[vec4]") {
    JTX::Util::Vec4 a{};

    REQUIRE(a.x == 0.0f);
    REQUIRE(a.y == 0.0f);
    REQUIRE(a.z == 0.0f);
    REQUIRE(a.w == 0.0f);
}

TEST_CASE("Vec3 xyz constructor sets x, y, z", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};

    REQUIRE(a.x == 1.0f);
    REQUIRE(a.y == 2.0f);
    REQUIRE(a.z == 3.0f);
}

TEST_CASE("Vec4 xyzw constructor sets x, y, z, w", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};

    REQUIRE(a.x == 1.0f);
    REQUIRE(a.y == 2.0f);
    REQUIRE(a.z == 3.0f);
    REQUIRE(a.w == 4.0f);
}

TEST_CASE("Vec3 (in)equality operator on equal vectors", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};
    JTX::Util::Vec3 b{1.0f, 2.0f, 3.0f};

    REQUIRE(a == b);
    REQUIRE_FALSE(a != b);
}

TEST_CASE("Vec3 (in)equality operator on unequal vectors", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};
    JTX::Util::Vec3 b{1.0f, 2.0f, 4.0f};

    REQUIRE_FALSE(a == b);
    REQUIRE(a != b);
}

TEST_CASE("Vec4 (in)equality operator on equal vectors", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};
    JTX::Util::Vec4 b{1.0f, 2.0f, 3.0f, 4.0f};

    REQUIRE(a == b);
    REQUIRE_FALSE(a != b);
}

TEST_CASE("Vec4 (in)equality operator on unequal vectors", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};
    JTX::Util::Vec4 b{1.0f, 2.0f, 3.0f, 5.0f};

    REQUIRE_FALSE(a == b);
    REQUIRE(a != b);
}

TEST_CASE("Vec3 addition", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};
    JTX::Util::Vec3 b{1.0f, 2.0f, 3.0f};

    JTX::Util::Vec3 c = a + b;

    REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(6.0f, 0.0001f));
}

TEST_CASE("Vec4 addition", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};
    JTX::Util::Vec4 b{1.0f, 2.0f, 3.0f, 4.0f};

    JTX::Util::Vec4 c = a + b;

    REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(6.0f, 0.0001f));
    REQUIRE_THAT(c.w, Catch::Matchers::WithinRel(8.0f, 0.0001f));
}

TEST_CASE("Vec3 subtraction", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};
    JTX::Util::Vec3 b{1.0f, 2.0f, 3.0f};

    JTX::Util::Vec3 c = a - b;

    REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(0.0f, 0.0001f));
}

TEST_CASE("Vec4 subtraction", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};
    JTX::Util::Vec4 b{1.0f, 2.0f, 3.0f, 4.0f};

    JTX::Util::Vec4 c = a - b;

    REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(c.w, Catch::Matchers::WithinRel(0.0f, 0.0001f));
}

TEST_CASE("Vec3 element-wise multiplication", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};
    JTX::Util::Vec3 b{1.0f, 2.0f, 3.0f};

    JTX::Util::Vec3 c = a * b;

    REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(9.0f, 0.0001f));
}

TEST_CASE("Vec4 element-wise multiplication", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};
    JTX::Util::Vec4 b{1.0f, 2.0f, 3.0f, 4.0f};

    JTX::Util::Vec4 c = a * b;

    REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(9.0f, 0.0001f));
    REQUIRE_THAT(c.w, Catch::Matchers::WithinRel(16.0f, 0.0001f));

}

TEST_CASE("Vec3 cross product", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, -2.0f, 3.0f};
    JTX::Util::Vec3 b{7.0f, 8.0f, -5.0f};

    JTX::Util::Vec3 c = a.cross(b);

    REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(-14.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(26.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(22.0f, 0.0001f));
}

TEST_CASE("Vec3 dot product", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};
    JTX::Util::Vec3 b{4.0f, 5.0f, 6.0f};

    float c = a.dot(b);

    REQUIRE_THAT(c, Catch::Matchers::WithinRel(32.0f, 0.0001f));
}

TEST_CASE("Vec4 dot prodcut", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};
    JTX::Util::Vec4 b{5.0f, 6.0f, 7.0f, 8.0f};

    float c = a.dot(b);

    REQUIRE_THAT(c, Catch::Matchers::WithinRel(70.0f, 0.0001f));
}

TEST_CASE("Vec3 dot product with separate x, y, z", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};

    float c = a.dot(4.0f, 5.0f, 6.0f);

    REQUIRE_THAT(c, Catch::Matchers::WithinRel(32.0f, 0.0001f));
}

TEST_CASE("Vec4 dot product with separate x, y, z, w", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};

    float c = a.dot(5.0f, 6.0f, 7.0f, 8.0f);

    REQUIRE_THAT(c, Catch::Matchers::WithinRel(70.0f, 0.0001f));
}


TEST_CASE("Vec3 length", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};

    float c = a.len();

    REQUIRE_THAT(c, Catch::Matchers::WithinRel(3.741657f, 0.0001f));
}

TEST_CASE("Vec4 length", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};

    float c = a.len();

    REQUIRE_THAT(c, Catch::Matchers::WithinRel(5.477226f, 0.0001f));
}

TEST_CASE("Vec3 normalize", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};

    a.normalize();

    REQUIRE_THAT(a.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
    REQUIRE_THAT(a.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
    REQUIRE_THAT(a.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

TEST_CASE("Vec4 normalize", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};

    a.normalize();

    REQUIRE_THAT(a.x, Catch::Matchers::WithinRel(0.182574f, 0.0001f));
    REQUIRE_THAT(a.y, Catch::Matchers::WithinRel(0.365148f, 0.0001f));
    REQUIRE_THAT(a.z, Catch::Matchers::WithinRel(0.547723f, 0.0001f));
    REQUIRE_THAT(a.w, Catch::Matchers::WithinRel(0.730297f, 0.0001f));
}

TEST_CASE("Vec3 normalize zero vector throws", "[vec3]") {
    JTX::Util::Vec3 a{0.0f, 0.0f, 0.0f};

    REQUIRE_THROWS_AS(a.normalize(), std::runtime_error);
}

TEST_CASE("Vec4 normalize zero vector throws", "[vec4]") {
    JTX::Util::Vec4 a{0.0f, 0.0f, 0.0f, 0.0f};

    REQUIRE_THROWS_AS(a.normalize(), std::runtime_error);
}

TEST_CASE("Vec3 normalized", "[vec3]") {
    JTX::Util::Vec3 a{1.0f, 2.0f, 3.0f};

    JTX::Util::Vec3 b = a.normalized();

    REQUIRE_THAT(b.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
    REQUIRE_THAT(b.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
    REQUIRE_THAT(b.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

TEST_CASE("Vec4 normalized", "[vec4]") {
    JTX::Util::Vec4 a{1.0f, 2.0f, 3.0f, 4.0f};

    JTX::Util::Vec4 b = a.normalized();

    REQUIRE_THAT(b.x, Catch::Matchers::WithinRel(0.182574f, 0.0001f));
    REQUIRE_THAT(b.y, Catch::Matchers::WithinRel(0.365148f, 0.0001f));
    REQUIRE_THAT(b.z, Catch::Matchers::WithinRel(0.547723f, 0.0001f));
    REQUIRE_THAT(b.w, Catch::Matchers::WithinRel(0.730297f, 0.0001f));
}

TEST_CASE("Vec3 normalized zero vector throws", "[vec3]") {
    JTX::Util::Vec3 a{0.0f, 0.0f, 0.0f};

    REQUIRE_THROWS_AS(a.normalized(), std::runtime_error);
}

TEST_CASE("Vec4 normalized zero vector throws", "[vec4]") {
    JTX::Util::Vec4 a{0.0f, 0.0f, 0.0f, 0.0f};

    REQUIRE_THROWS_AS(a.normalized(), std::runtime_error);
}

TEST_CASE("Mat4 default constructor is identity matrix", "[mat4]") {
    JTX::Util::Mat4 a{};

    REQUIRE(a.data[0][0] == 1.0f);
    REQUIRE(a.data[0][1] == 0.0f);
    REQUIRE(a.data[0][2] == 0.0f);
    REQUIRE(a.data[0][3] == 0.0f);

    REQUIRE(a.data[1][0] == 0.0f);
    REQUIRE(a.data[1][1] == 1.0f);
    REQUIRE(a.data[1][2] == 0.0f);
    REQUIRE(a.data[1][3] == 0.0f);

    REQUIRE(a.data[2][0] == 0.0f);
    REQUIRE(a.data[2][1] == 0.0f);
    REQUIRE(a.data[2][2] == 1.0f);
    REQUIRE(a.data[2][3] == 0.0f);

    REQUIRE(a.data[3][0] == 0.0f);
    REQUIRE(a.data[3][1] == 0.0f);
    REQUIRE(a.data[3][2] == 0.0f);
    REQUIRE(a.data[3][3] == 1.0f);
}

TEST_CASE("Mat4 equality operator on equal matrices", "[mat4]") {
    JTX::Util::Mat4 a{};
    JTX::Util::Mat4 b{};

    REQUIRE(a == b);
    REQUIRE_FALSE(a != b);
}

TEST_CASE("Mat4 equality operator on unequal matrices", "[mat4]") {
    JTX::Util::Mat4 a{};
    JTX::Util::Mat4 b{};
    b.data[0][0] = 2.0f;

    REQUIRE_FALSE(a == b);
    REQUIRE(a != b);
}

TEST_CASE("degToRad 90deg", "[misc]") {
    float a = JTX::Util::degToRad(90.0f);

    REQUIRE_THAT(a, Catch::Matchers::WithinRel(1.570796f, 0.0001f));
}

TEST_CASE("Mat4 90deg X-axis rotation", "[mat4]") {
    JTX::Util::Mat4 a = JTX::Util::Mat4::rotation(JTX::Util::degToRad(90.0f), JTX::Util::Axis::X);

    REQUIRE_THAT(a.data[0][0], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][2], Catch::Matchers::WithinRel(-1.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][1], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][3], Catch::Matchers::WithinRel(1.0f, 0.0001f));
}

TEST_CASE("Mat4 90deg Y-axis rotation", "[mat4]") {
    JTX::Util::Mat4 a = JTX::Util::Mat4::rotation(JTX::Util::degToRad(90.0f), JTX::Util::Axis::Y);

    REQUIRE_THAT(a.data[0][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][2], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][1], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][0], Catch::Matchers::WithinRel(-1.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][3], Catch::Matchers::WithinRel(1.0f, 0.0001f));
}

TEST_CASE("Mat4 90deg Z-axis rotation", "[mat4]") {
    JTX::Util::Mat4 a = JTX::Util::Mat4::rotation(JTX::Util::degToRad(90.0f), JTX::Util::Axis::Z);

    REQUIRE_THAT(a.data[0][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][1], Catch::Matchers::WithinRel(-1.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][0], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][2], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][3], Catch::Matchers::WithinRel(1.0f, 0.0001f));
}

TEST_CASE("Mat4 scale 1:2:3", "[mat4]") {
    JTX::Util::Mat4 a = JTX::Util::Mat4::scale(1.0f, 2.0f, 3.0f);

    REQUIRE_THAT(a.data[0][0], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][1], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][2], Catch::Matchers::WithinRel(3.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][3], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][3], Catch::Matchers::WithinRel(1.0f, 0.0001f));
}

TEST_CASE("Mat4 translation 1:2:3", "[mat4]") {
    JTX::Util::Mat4 a = JTX::Util::Mat4::translation(1.0f, 2.0f, 3.0f);

    REQUIRE_THAT(a.data[0][0], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[0][3], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][1], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[1][3], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][2], Catch::Matchers::WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(a.data[2][3], Catch::Matchers::WithinRel(3.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][0], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][1], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][2], Catch::Matchers::WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(a.data[3][3], Catch::Matchers::WithinRel(1.0f, 0.0001f));
}

TEST_CASE("Mat4 matmul identity matrix", "[mat4]") {
    JTX::Util::Mat4 a{};
    JTX::Util::Mat4 b{};

    JTX::Util::Mat4 c = JTX::Util::Mat4::matmul(a, b);

    REQUIRE(c == a);
}

TEST_CASE("Mat4 matmul scale and translation", "[mat4]") {
    JTX::Util::Mat4 s = JTX::Util::Mat4::scale(2.0f, 2.0f, 2.0f);
    JTX::Util::Mat4 t = JTX::Util::Mat4::translation(1.0f, 1.0f, 1.0f);

    JTX::Util::Mat4 c = JTX::Util::Mat4::matmul(s, t);

    REQUIRE_THAT(c.data[0][0], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.data[0][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[0][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[0][3], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.data[1][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[1][1], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.data[1][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[1][3], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.data[2][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[2][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[2][2], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.data[2][3], Catch::Matchers::WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(c.data[3][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[3][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[3][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(c.data[3][3], Catch::Matchers::WithinRel(1.0f, 0.0001f));
}

TEST_CASE("Mat4 * operator identity matrix", "[mat4]") {
    JTX::Util::Mat4 a{};
    JTX::Util::Mat4 b{};

    JTX::Util::Mat4 c = a * b;

    REQUIRE(c == a);
}

TEST_CASE("Test IDPool", "[idpool]") {
    JTX::Util::IDPool pool{};

    REQUIRE(pool.getID() == 0);
    REQUIRE(pool.getID() == 1);
    REQUIRE(pool.getID() == 2);
    pool.releaseID(1);
    REQUIRE(pool.getID() == 1);
    REQUIRE(pool.getID() == 3);
}
