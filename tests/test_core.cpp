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

  REQUIRE_THAT(dl.calculateIntensity(JTX::Util::Vec3f(-1.0f, -1.0f, -1.0f)),
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

  float intensity = dl.calculateIntensity(p.getFaceNormal(3));
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

TEST_CASE("Test camera view matrix", "[Camera]") {
  JTX::Core::Camera cam(
      JTX::Util::Vec3f(0.0f, 0.0f, 30.0f), JTX::Util::Vec3f(0.0f, 0.0f, 0.0f),
      JTX::Util::Vec3f(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);

  auto vmat = cam.getViewMatrix();
  REQUIRE_THAT(vmat.data[0][0], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[0][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[0][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[0][3], Catch::Matchers::WithinAbs(0.0f, 0.0001f));

  REQUIRE_THAT(vmat.data[1][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[1][1], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[1][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[1][3], Catch::Matchers::WithinAbs(0.0f, 0.0001f));

  REQUIRE_THAT(vmat.data[2][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[2][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[2][2], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[2][3], Catch::Matchers::WithinAbs(-30.0f, 0.0001f));

  REQUIRE_THAT(vmat.data[3][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[3][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[3][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(vmat.data[3][3], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
}

TEST_CASE("Test camera perspective projection matrix", "[Camera]") {
  JTX::Core::Camera cam(
      JTX::Util::Vec3f(0.0f, 0.0f, 30.0f), JTX::Util::Vec3f(0.0f, 0.0f, 0.0f),
      JTX::Util::Vec3f(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);

  auto pmat = cam.getProjMatrix(2.0f, JTX::Core::PERSPECTIVE);
  REQUIRE_THAT(pmat.data[0][0],
               Catch::Matchers::WithinAbs(0.86602295, 0.0001f));
  REQUIRE_THAT(pmat.data[0][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[0][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[0][3], Catch::Matchers::WithinAbs(0.0f, 0.0001f));

  REQUIRE_THAT(pmat.data[1][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[1][1],
               Catch::Matchers::WithinAbs(1.73204591, 0.0001f));
  REQUIRE_THAT(pmat.data[1][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[1][3], Catch::Matchers::WithinAbs(0.0f, 0.0001f));

  REQUIRE_THAT(pmat.data[2][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[2][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[2][2], Catch::Matchers::WithinAbs(1.002002, 0.0001f));
  REQUIRE_THAT(pmat.data[2][3], Catch::Matchers::WithinAbs(0.2002002, 0.0001f));

  REQUIRE_THAT(pmat.data[3][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[3][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[3][2], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
  REQUIRE_THAT(pmat.data[3][3], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
}

TEST_CASE("Test scene add primitive and dirlight", "[Scene]") {
  JTX::Core::Camera cam(
      JTX::Util::Vec3f(0.0f, 0.0f, 30.0f), JTX::Util::Vec3f(0.0f, 0.0f, 0.0f),
      JTX::Util::Vec3f(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);
  JTX::Core::Scene scene(cam);

  auto p = std::make_unique<JTX::Core::Primitive>();
  p->load(CUBE_PATH);
  auto l = scene.addPrimitive(std::move(p));

  auto dl = std::make_unique<JTX::Core::DirLight>(
      JTX::Util::Vec3f(1.0f, 1.0f, 1.0f), 1.0f);
  auto light = scene.addLight(std::move(dl));

  REQUIRE(scene.getNumPrimitives() == 1);
  REQUIRE(scene.getNumLights() == 1);

  REQUIRE(scene.getPrimitive(l).getNumVertices() == 8);
  REQUIRE(scene.getPrimitive(l).getNumFaces() == 12);

  REQUIRE(scene.getLight(light).getIntensity() == 1.0f);

  JTX::Util::Vec3f pos = scene.getCamera().getPos();

  REQUIRE(pos.x == 0.0f);
  REQUIRE(pos.y == 0.0f);
  REQUIRE(pos.z == 30.0f);
}

TEST_CASE("Test scene remove primitive and dirlight", "[Scene]") {
  JTX::Core::Camera cam(
      JTX::Util::Vec3f(0.0f, 0.0f, 30.0f), JTX::Util::Vec3f(0.0f, 0.0f, 0.0f),
      JTX::Util::Vec3f(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);
  JTX::Core::Scene scene(cam);

  auto p = std::make_unique<JTX::Core::Primitive>();
  p->load(CUBE_PATH);
  auto primitiveId = scene.addPrimitive(std::move(p));

  auto dl = std::make_unique<JTX::Core::DirLight>(
      JTX::Util::Vec3f(1.0f, 1.0f, 1.0f), 1.0f);
  auto lightId = scene.addLight(std::move(dl));

  REQUIRE(scene.getNumPrimitives() == 1);
  REQUIRE(scene.getNumLights() == 1);

  scene.removePrimitive(primitiveId);
  scene.removeLight(lightId);

  REQUIRE(scene.getNumPrimitives() == 0);
  REQUIRE(scene.getNumLights() == 0);

  REQUIRE_THROWS_AS(scene.getPrimitive(primitiveId), std::runtime_error);
  REQUIRE_THROWS_AS(scene.getLight(lightId), std::runtime_error);
}

TEST_CASE("Test scene remove primitive in middle maintains index", "[Scene]") {
  JTX::Core::Scene scene(JTX::Core::DEFAULT_CAM);

  auto p1 = std::make_unique<JTX::Core::Primitive>();
  auto p2 = std::make_unique<JTX::Core::Primitive>();
  auto p3 = std::make_unique<JTX::Core::Primitive>();
  p1->load(CUBE_PATH);
  p2->load(CUBE_PATH);
  p3->load(HEAD_PATH);

  int p1v = p1->getNumVertices();
  int p3v = p3->getNumVertices();

  auto id1 = scene.addPrimitive(std::move(p1));
  auto id2 = scene.addPrimitive(std::move(p2));
  auto id3 = scene.addPrimitive(std::move(p3));

  REQUIRE(scene.getNumPrimitives() == 3);

  scene.removePrimitive(id2);

  REQUIRE(scene.getNumPrimitives() == 2);

  auto p1v2 = scene.getPrimitive(id1).getNumVertices();
  auto p3v2 = scene.getPrimitive(id3).getNumVertices();

  REQUIRE(p1v == p1v2);
  REQUIRE(p3v == p3v2);
}

TEST_CASE("Test scene remove light in middle maintains index", "[Scene]") {
  JTX::Core::Scene scene(JTX::Core::DEFAULT_CAM);

  auto l1 = std::make_unique<JTX::Core::DirLight>(
      JTX::Util::Vec3f(1.0f, 1.0f, 1.0f), 0.25f);
  auto l2 = std::make_unique<JTX::Core::DirLight>(
      JTX::Util::Vec3f(1.0f, 1.0f, 1.0f), 0.5f);
  auto l3 = std::make_unique<JTX::Core::DirLight>(
      JTX::Util::Vec3f(1.0f, 1.0f, 1.0f), 0.75f);

  auto id1 = scene.addLight(std::move(l1));
  auto id2 = scene.addLight(std::move(l2));
  auto id3 = scene.addLight(std::move(l3));

  float l1i = scene.getLight(id1).getIntensity();
  float l3i = scene.getLight(id3).getIntensity();

  REQUIRE(scene.getNumLights() == 3);

  scene.removeLight(id2);

  REQUIRE(scene.getNumLights() == 2);

  float l1i2 = scene.getLight(id1).getIntensity();
  float l3i2 = scene.getLight(id3).getIntensity();

  REQUIRE(l1i == l1i2);
  REQUIRE(l3i == l3i2);
}