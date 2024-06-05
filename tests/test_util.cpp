#include "JTX/util/util.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// Vec3f
TEST_CASE("Vec3f default constructor is zero vector", "[vec3f]") {
  JTX::Util::Vec3f a{};

  REQUIRE(a.x == 0.0f);
  REQUIRE(a.y == 0.0f);
  REQUIRE(a.z == 0.0f);
}

TEST_CASE("Vec3f xyz constructor sets x, y, z", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};

  REQUIRE(a.x == 1.0f);
  REQUIRE(a.y == 2.0f);
  REQUIRE(a.z == 3.0f);
}

TEST_CASE("Vec3f (in)equality operator on equal vectors", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};
  JTX::Util::Vec3f b{1.0f, 2.0f, 3.0f};

  REQUIRE(a == b);
  REQUIRE_FALSE(a != b);
}

TEST_CASE("Vec3f (in)equality operator on unequal vectors", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};
  JTX::Util::Vec3f b{1.0f, 2.0f, 4.0f};

  REQUIRE_FALSE(a == b);
  REQUIRE(a != b);
}

TEST_CASE("Vec3f addition", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};
  JTX::Util::Vec3f b{1.0f, 2.0f, 3.0f};

  JTX::Util::Vec3f c = a + b;

  REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(2.0f, 0.0001f));
  REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
  REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(6.0f, 0.0001f));
}

TEST_CASE("Vec3f subtraction", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};
  JTX::Util::Vec3f b{1.0f, 2.0f, 3.0f};

  JTX::Util::Vec3f c = a - b;

  REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(0.0f, 0.0001f));
  REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(0.0f, 0.0001f));
  REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(0.0f, 0.0001f));
}

TEST_CASE("Vec3f element-wise multiplication", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};
  JTX::Util::Vec3f b{1.0f, 2.0f, 3.0f};

  JTX::Util::Vec3f c = a * b;

  REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(1.0f, 0.0001f));
  REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
  REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(9.0f, 0.0001f));
}

TEST_CASE("Vec3f cross product", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, -2.0f, 3.0f};
  JTX::Util::Vec3f b{7.0f, 8.0f, -5.0f};

  JTX::Util::Vec3f c = a.cross(b);

  REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(-14.0f, 0.0001f));
  REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(26.0f, 0.0001f));
  REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(22.0f, 0.0001f));
}

TEST_CASE("Vec3f dot product", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};
  JTX::Util::Vec3f b{4.0f, 5.0f, 6.0f};

  float c = a.dot(b);

  REQUIRE_THAT(c, Catch::Matchers::WithinRel(32.0f, 0.0001f));
}

TEST_CASE("Vec3f dot product with separate x, y, z", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};

  float c = a.dot(4.0f, 5.0f, 6.0f);

  REQUIRE_THAT(c, Catch::Matchers::WithinRel(32.0f, 0.0001f));
}

TEST_CASE("Vec3f length", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};

  float c = a.len();

  REQUIRE_THAT(c, Catch::Matchers::WithinRel(3.741657f, 0.0001f));
}

TEST_CASE("Vec3f normalize", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};

  a.normalize();

  REQUIRE_THAT(a.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
  REQUIRE_THAT(a.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
  REQUIRE_THAT(a.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

TEST_CASE("Vec3f normalized", "[Vec3f]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};

  JTX::Util::Vec3f b = a.normalized();

  REQUIRE_THAT(b.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
  REQUIRE_THAT(b.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
  REQUIRE_THAT(b.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

// Vec4f
TEST_CASE("Vec4f default constructor is zero vector", "[Vec4f]") {
  JTX::Util::Vec4f a{};

  REQUIRE(a.x == 0.0f);
  REQUIRE(a.y == 0.0f);
  REQUIRE(a.z == 0.0f);
  REQUIRE(a.w == 0.0f);
}

TEST_CASE("Vec4f xyzw constructor sets x, y, z, w", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};

  REQUIRE(a.x == 1.0f);
  REQUIRE(a.y == 2.0f);
  REQUIRE(a.z == 3.0f);
  REQUIRE(a.w == 4.0f);
}

TEST_CASE("Vec4f (in)equality operator on equal vectors", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};
  JTX::Util::Vec4f b{1.0f, 2.0f, 3.0f, 4.0f};

  REQUIRE(a == b);
  REQUIRE_FALSE(a != b);
}

TEST_CASE("Vec4f (in)equality operator on unequal vectors", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};
  JTX::Util::Vec4f b{1.0f, 2.0f, 3.0f, 5.0f};

  REQUIRE_FALSE(a == b);
  REQUIRE(a != b);
}

TEST_CASE("Vec4f addition", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};
  JTX::Util::Vec4f b{1.0f, 2.0f, 3.0f, 4.0f};

  JTX::Util::Vec4f c = a + b;

  REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(2.0f, 0.0001f));
  REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
  REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(6.0f, 0.0001f));
  REQUIRE_THAT(c.w, Catch::Matchers::WithinRel(8.0f, 0.0001f));
}

TEST_CASE("Vec4f subtraction", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};
  JTX::Util::Vec4f b{1.0f, 2.0f, 3.0f, 4.0f};

  JTX::Util::Vec4f c = a - b;

  REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(0.0f, 0.0001f));
  REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(0.0f, 0.0001f));
  REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(0.0f, 0.0001f));
  REQUIRE_THAT(c.w, Catch::Matchers::WithinRel(0.0f, 0.0001f));
}

TEST_CASE("Vec4f element-wise multiplication", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};
  JTX::Util::Vec4f b{1.0f, 2.0f, 3.0f, 4.0f};

  JTX::Util::Vec4f c = a * b;

  REQUIRE_THAT(c.x, Catch::Matchers::WithinRel(1.0f, 0.0001f));
  REQUIRE_THAT(c.y, Catch::Matchers::WithinRel(4.0f, 0.0001f));
  REQUIRE_THAT(c.z, Catch::Matchers::WithinRel(9.0f, 0.0001f));
  REQUIRE_THAT(c.w, Catch::Matchers::WithinRel(16.0f, 0.0001f));
}

TEST_CASE("Vec4f dot prodcut", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};
  JTX::Util::Vec4f b{5.0f, 6.0f, 7.0f, 8.0f};

  float c = a.dot(b);

  REQUIRE_THAT(c, Catch::Matchers::WithinRel(70.0f, 0.0001f));
}

TEST_CASE("Vec4f dot product with separate x, y, z, w", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};

  float c = a.dot(5.0f, 6.0f, 7.0f, 8.0f);

  REQUIRE_THAT(c, Catch::Matchers::WithinRel(70.0f, 0.0001f));
}

TEST_CASE("Vec4f length", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};

  float c = a.len();

  REQUIRE_THAT(c, Catch::Matchers::WithinRel(5.477226f, 0.0001f));
}

TEST_CASE("Vec4f normalize", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};

  a.normalize();

  REQUIRE_THAT(a.x, Catch::Matchers::WithinRel(0.182574f, 0.0001f));
  REQUIRE_THAT(a.y, Catch::Matchers::WithinRel(0.365148f, 0.0001f));
  REQUIRE_THAT(a.z, Catch::Matchers::WithinRel(0.547723f, 0.0001f));
  REQUIRE_THAT(a.w, Catch::Matchers::WithinRel(0.730297f, 0.0001f));
}

TEST_CASE("Vec4f normalized", "[Vec4f]") {
  JTX::Util::Vec4f a{1.0f, 2.0f, 3.0f, 4.0f};

  JTX::Util::Vec4f b = a.normalized();

  REQUIRE_THAT(b.x, Catch::Matchers::WithinRel(0.182574f, 0.0001f));
  REQUIRE_THAT(b.y, Catch::Matchers::WithinRel(0.365148f, 0.0001f));
  REQUIRE_THAT(b.z, Catch::Matchers::WithinRel(0.547723f, 0.0001f));
  REQUIRE_THAT(b.w, Catch::Matchers::WithinRel(0.730297f, 0.0001f));
}

// Vec2i
TEST_CASE("Vec2i default constructor is zero vector", "[Vec2i]") {
  JTX::Util::Vec2i a{};

  REQUIRE(a.x == 0);
  REQUIRE(a.y == 0);
}

TEST_CASE("Vec2i xyz constructor sets x, y", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};

  REQUIRE(a.x == 1);
  REQUIRE(a.y == 2);
}

TEST_CASE("Vec2i (in)equality operator on equal vectors", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};
  JTX::Util::Vec2i b{1, 2};

  REQUIRE(a == b);
  REQUIRE_FALSE(a != b);
}

TEST_CASE("Vec2i (in)equality operator on unequal vectors", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};
  JTX::Util::Vec2i b{1, 3};

  REQUIRE_FALSE(a == b);
  REQUIRE(a != b);
}

TEST_CASE("Vec2i addition", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};
  JTX::Util::Vec2i b{1, 2};

  JTX::Util::Vec2i c = a + b;

  REQUIRE(c.x == 2);
  REQUIRE(c.y == 4);
}

TEST_CASE("Vec2i subtraction", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};
  JTX::Util::Vec2i b{1, 2};

  JTX::Util::Vec2i c = a - b;

  REQUIRE(c.x == 0);
  REQUIRE(c.y == 0);
}

TEST_CASE("Vec2i element-wise multiplication", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};
  JTX::Util::Vec2i b{1, 2};

  JTX::Util::Vec2i c = a * b;

  REQUIRE(c.x == 1);
  REQUIRE(c.y == 4);
}

TEST_CASE("Vec2i dot product", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};
  JTX::Util::Vec2i b{1, 2};

  int c = a.dot(b);

  REQUIRE(c == 5);
}

TEST_CASE("Vec2i dot product with separate x, y, z", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};

  int c = a.dot(1, 2);

  REQUIRE(c == 5);
}

TEST_CASE("Vec2i length", "[Vec2i]") {
  JTX::Util::Vec2i a{1, 2};

  float c = a.len();

  REQUIRE_THAT(c, Catch::Matchers::WithinRel(2.236067f, 0.0001f));
}

TEST_CASE("Vec2i normalize", "[Vec2i]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};

  a.normalize();

  REQUIRE_THAT(a.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
  REQUIRE_THAT(a.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
  REQUIRE_THAT(a.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

TEST_CASE("Vec2i normalized", "[Vec2i]") {
  JTX::Util::Vec3f a{1.0f, 2.0f, 3.0f};

  JTX::Util::Vec3f b = a.normalized();

  REQUIRE_THAT(b.x, Catch::Matchers::WithinRel(0.267261f, 0.0001f));
  REQUIRE_THAT(b.y, Catch::Matchers::WithinRel(0.534522f, 0.0001f));
  REQUIRE_THAT(b.z, Catch::Matchers::WithinRel(0.801784f, 0.0001f));
}

// Mat4
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
  JTX::Util::Mat4 a =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(90.0f), JTX::Util::Axis::X);

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
  JTX::Util::Mat4 a =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(90.0f), JTX::Util::Axis::Y);

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
  JTX::Util::Mat4 a =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(90.0f), JTX::Util::Axis::Z);

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

// TEST_CASE("Test Vec4f applyTransform", "[Vec4f]") {
//     JTX::Util::Vec4f a{1.0f, -1.0f, -1.0f, 1.0f};
//     JTX::Util::Mat4 rot =
//     JTX::Util::Mat4::rotation(JTX::Util::degToRad(25.0f),
//     JTX::Util::Axis::X); a.applyTransform(&rot);
//
//     REQUIRE_THAT(a.x, Catch::Matchers::WithinRel(1.0f, 0.0001f));
//     REQUIRE_THAT(a.y, Catch::Matchers::WithinRel(-0.48368953f, 0.0001f));
//     REQUIRE_THAT(a.z, Catch::Matchers::WithinRel(-1.32892605f, 0.0001f));
// }

TEST_CASE("Test Mat4 [] operators", "[mat4]") {
  JTX::Util::Mat4 m{};

  REQUIRE(m[0][0] == 1.0f);
  REQUIRE(m[0][1] == 0.0f);
  REQUIRE(m[0][2] == 0.0f);
  REQUIRE(m[0][3] == 0.0f);
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
