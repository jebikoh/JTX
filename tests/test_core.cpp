//
// Created by Jayden Edara on 4/3/24.
//
#include "JTX/core/core.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

static const std::string CUBE_PATH = "../../Tests/primitives/cube.obj";
static const std::string HEAD_PATH = "../../Tests/primitives/head.obj";

TEST_CASE("Primitive loads mesh from .obj file (cube: v, f)", "[Primitive]") {
  JTX::Core::Primitive p;
  p.load(CUBE_PATH);

  REQUIRE(p.getNumVertices() == 8);
  REQUIRE(p.getNumFaces() == 12);

  REQUIRE_THAT(p.getVertex(0).x, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(0).y, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(0).z, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(1).x, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(1).y, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(1).z, Catch::Matchers::WithinAbs(1.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(2).x, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(2).y, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(2).z, Catch::Matchers::WithinAbs(1.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(3).x, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(3).y, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(3).z, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(4).x, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(4).y, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(4).z, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(5).x, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(5).y, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(5).z, Catch::Matchers::WithinAbs(1.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(6).x, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(6).y, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(6).z, Catch::Matchers::WithinAbs(1.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(7).x, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(7).y, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(7).z, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

  REQUIRE(p.getFace(0)->v1 == 1);
  REQUIRE(p.getFace(0)->v2 == 2);
  REQUIRE(p.getFace(0)->v3 == 3);

  REQUIRE(p.getFace(11)->v1 == 4);
  REQUIRE(p.getFace(11)->v2 == 0);
  REQUIRE(p.getFace(11)->v3 == 7);
}

// This test doesn't actually test texture coordinates
// TODO: update test when object with vts are added
TEST_CASE("Primitive loads mesh vertex normals", "[Primitive]") {
  JTX::Core::Primitive p;
  p.load(HEAD_PATH);

  REQUIRE(p.getNumVertices() == 1500);
  REQUIRE(p.getNumFaces() == 2996);
  REQUIRE(p.getNumVertexTextures() == 0);
  REQUIRE(p.getNumVertexNormals() == 3006);
  REQUIRE_THAT(p.getVertexNormal(0).x,
               Catch::Matchers::WithinAbs(0.7316f, 0.0001f));
  REQUIRE_THAT(p.getVertexNormal(0).y,
               Catch::Matchers::WithinAbs(0.3682f, 0.0001f));
  REQUIRE_THAT(p.getVertexNormal(0).z,
               Catch::Matchers::WithinAbs(0.5737f, 0.0001f));
}

TEST_CASE("Primitive normal calculations", "[Primitive]") {
  JTX::Core::Primitive p;
  p.load(CUBE_PATH);
  p.calculateNormals();

  REQUIRE_THAT(p.getFaceNormal(0).x, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(p.getFaceNormal(0).y,
               Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(p.getFaceNormal(0).z, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(p.getFaceNormal(p.getNumFaces() - 1).x,
               Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(p.getFaceNormal(p.getNumFaces() - 1).y,
               Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(p.getFaceNormal(p.getNumFaces() - 1).z,
               Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
}

TEST_CASE("Test cube rotation XY", "[Primitive]") {
  JTX::Core::Primitive p;
  p.load(CUBE_PATH);

  float rad = JTX::Util::degToRad(45);
  JTX::Util::Mat4 rot_x = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);
  JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);

  p.applyTransform(&rot_x);
  p.applyTransform(&rot_y);

  JTX::Util::Vec4f v0 = p.getVertex(0);

  REQUIRE_THAT(v0.x, Catch::Matchers::WithinAbs(-0.292893219f, 0.0001f));
  REQUIRE_THAT(v0.y, Catch::Matchers::WithinAbs(0.000f, 0.0001f));
  REQUIRE_THAT(v0.z, Catch::Matchers::WithinAbs(-1.70710678f, 0.0001f));
}

TEST_CASE("Rotated cube normal calculation", "[Primitive]") {
  JTX::Core::Primitive p;
  p.load(CUBE_PATH);

  float rad = JTX::Util::degToRad(45);
  JTX::Util::Mat4 rot_x = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);
  JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);
  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(5.0f, 5.0f, 5.0f);
  p.applyTransform(&rot_x);
  p.applyTransform(&rot_y);
  p.applyTransform(&scale);
  p.calculateNormals();

  REQUIRE_THAT(p.getFaceNormal(0).x,
               Catch::Matchers::WithinAbs(-0.5000f, 0.0001f));
  REQUIRE_THAT(p.getFaceNormal(0).y,
               Catch::Matchers::WithinAbs(-0.707106781f, 0.0001f));
  REQUIRE_THAT(p.getFaceNormal(0).z,
               Catch::Matchers::WithinAbs(-0.5f, 0.0001f));
}

TEST_CASE("Apply scale transformation to cube primitive", "[Primitive]") {
  JTX::Core::Primitive p;
  p.load(CUBE_PATH);

  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(2.0f, 2.0f, 2.0f);
  p.applyTransform(&scale);

  REQUIRE_THAT(p.getVertex(0).x, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(0).y, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(0).z, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(1).x, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(1).y, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(1).z, Catch::Matchers::WithinAbs(2.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(2).x, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(2).y, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(2).z, Catch::Matchers::WithinAbs(2.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(3).x, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(3).y, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(3).z, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(4).x, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(4).y, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(4).z, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(5).x, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(5).y, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(5).z, Catch::Matchers::WithinAbs(2.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(6).x, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(6).y, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(6).z, Catch::Matchers::WithinAbs(2.0f, 0.0001f));

  REQUIRE_THAT(p.getVertex(7).x, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(7).y, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
  REQUIRE_THAT(p.getVertex(7).z, Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

  REQUIRE(p.getFace(0)->v1 == 1);
  REQUIRE(p.getFace(0)->v2 == 2);
  REQUIRE(p.getFace(0)->v3 == 3);

  REQUIRE(p.getFace(11)->v1 == 4);
  REQUIRE(p.getFace(11)->v2 == 0);
  REQUIRE(p.getFace(11)->v3 == 7);
}

TEST_CASE("Test DirLight intensity", "[Lights]") {
  JTX::Core::DirLight dl(JTX::Util::Vec3f(1.0f, 1.0f, 1.0f), 1.0f);

  REQUIRE_THAT(dl.getIntensity(JTX::Util::Vec3f(-1.0f, -1.0f, -1.0f)),
               Catch::Matchers::WithinAbs(1.7320508075688776f, 0.0001f));
}

TEST_CASE("Test DirLight intensity with primitive", "[Primitive]") {
  JTX::Core::Primitive p;
  p.load(CUBE_PATH);

  float rad = JTX::Util::degToRad(45);
  JTX::Util::Mat4 rot_x = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);
  JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);
  p.applyTransform(&rot_x);
  p.applyTransform(&rot_y);
  p.calculateNormals();

  JTX::Core::DirLight dl(JTX::Util::Vec3f(0.0f, 0.0f, -1.0f), 1.0f);

  float intensity = dl.getIntensity(p.getFaceNormal(3));
  REQUIRE_THAT(intensity, Catch::Matchers::WithinAbs(0.5f, 0.0001f));
}

TEST_CASE("Test camera constructor", "[Camera]") {
  JTX::Core::Camera cam(
      JTX::Util::Vec3f(0.0f, 0.0f, 30.0f), JTX::Util::Vec3f(0.0f, 0.0f, 0.0f),
      JTX::Util::Vec3f(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);

  REQUIRE_THAT(cam.getPos().x, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(cam.getPos().y, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(cam.getPos().z, Catch::Matchers::WithinAbs(30.0f, 0.0001f));
  REQUIRE_THAT(cam.getLookAt().x, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(cam.getLookAt().y, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(cam.getLookAt().z, Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(cam.getUp().x, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(cam.getUp().y, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(cam.getUp().z, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(cam.getFov(), Catch::Matchers::WithinAbs(1.0472f, 0.0001f));
  REQUIRE_THAT(cam.getNear(), Catch::Matchers::WithinAbs(0.1f, 0.0001f));
  REQUIRE_THAT(cam.getFar(), Catch::Matchers::WithinAbs(100.0f, 0.0001f));
}
