// These tests (more like samples) are for visual inspection.

#include "JTX/core/core.hpp"
#include "JTX/util/util.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>

static const std::string CUBE_PATH = "../../Tests/primitives/cube.obj";
static const std::string HEAD_PATH = "../../Tests/primitives/head.obj";
static const std::string GT3_PATH = "../../Tests/primitives/gt3rs.obj";

static const bool ENABLE_STRESS_TESTS = true;

TEST_CASE("Renderer saveFb() with crossing lines", "[SaveFB]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1000, 1000, &shader, 3);
  r.drawLine(500, 0, 500, 999, JTX::Util::WHITE);
  r.drawLine(0, 500, 999, 500, JTX::Util::WHITE);
  r.drawLine(0, 0, 999, 999, JTX::Util::WHITE);
  r.drawLine(0, 999, 999, 0, JTX::Util::WHITE);
  r.saveFb("vertical_line.png", 0);
}

TEST_CASE("Cube wireframe", "[SaveFB]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1000, 1000, &shader, 3);
  JTX::Core::Primitive m{};
  m.load(CUBE_PATH);

  float rad = JTX::Util::degToRad(45);
  JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);
  JTX::Util::Mat4 rot_z = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);
  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(0.5, 0.5, 0.5);

  m.applyTransform(&rot_y);
  m.applyTransform(&rot_z);
  m.applyTransform(&scale);

  r.renderWireframe(m, JTX::Util::WHITE);
  r.saveFb("cube_wireframe.png", 0);
}

TEST_CASE("Head wireframe", "[SaveFB]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1000, 1000, &shader, 3);
  JTX::Core::Primitive m{};
  m.load(HEAD_PATH);

  JTX::Util::Mat4 rot_z =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(180), JTX::Util::Axis::Z);

  m.applyTransform(&rot_z);
  r.renderWireframe(m, JTX::Util::WHITE);
  r.saveFb("head_wireframe.png", 0);
}

TEST_CASE("Test draw triangle", "[SaveFB]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1000, 1000, &shader, 3);
  r.drawTriangle({300, 300}, 1.0f, {700, 300}, 1.0f, {500, 700}, 1.0f,
                 JTX::Util::WHITE);
  r.saveFb("triangle.png", 0);
}

TEST_CASE("Head perspective projection", "[SaveFB]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(2000, 2000, &shader, 3);

  JTX::Core::Primitive m{};
  m.load(HEAD_PATH);

  JTX::Util::Mat4 rot_z =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(180), JTX::Util::Axis::Z);
  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(40.0f, 40.0f, 40.0f);
  m.applyTransform(&rot_z);
  m.applyTransform(&scale);
  m.calculateNormals();

  JTX::Util::Vec3f pos{0.0f, 0.0f, 100.0f};
  JTX::Util::Vec3f target{0.0f, 0.0f, 0.0f};
  JTX::Util::Vec3f up{0.0f, 1.0f, 0.0f};
  JTX::Core::Camera cam(pos, target, up, 1.0472f, 0.1f, 1000.0f);

  JTX::Core::DirLight light({0.0f, 0.0f, -1.0f}, 1.0f);

  JTX::Core::Scene scene{cam};
  scene.addPrimitive(m);
  scene.addLight(light);

  r.render(&scene);
  r.saveFb("head_perspective.png", 0);
}

TEST_CASE("Cube perspective projection", "[SaveFB]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1000, 1000, &shader, 3);

  JTX::Core::Primitive m{};
  m.load(CUBE_PATH);

  float rad = JTX::Util::degToRad(45);
  JTX::Util::Mat4 rot_x = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);
  JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);
  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(5.0f, 5.0f, 5.0f);
  m.applyTransform(&rot_x);
  m.applyTransform(&rot_y);
  m.applyTransform(&scale);
  m.calculateNormals();

  JTX::Util::Vec3f pos{0.0f, 0.0f, 30.0f};
  JTX::Util::Vec3f target{0.0f, 0.0f, 0.0f};
  JTX::Util::Vec3f up{0.0f, 1.0f, 0.0f};
  JTX::Core::Camera cam(pos, target, up, 1.0472f, 0.1f, 100.0f);

  JTX::Core::DirLight light({0.0f, 0.0f, -1.0f}, 1.0f);

  JTX::Core::Scene scene{cam};
  scene.addPrimitive(m);
  scene.addLight(light);

  r.render(&scene);
  r.saveFb("cube_perspective.png", 0);
}

TEST_CASE("Perspective projection stress test", "[Stress]") {
  if (ENABLE_STRESS_TESTS == false) {
    return;
  }
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1920, 1080, &shader, 3);

  JTX::Core::Primitive m{};
  m.load(GT3_PATH);

  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(7.0f, 7.0f, 7.0f);
  JTX::Util::Mat4 rot_z = JTX::Util::Mat4::rotation(JTX::Util::degToRad(180.0f),
                                                    JTX::Util::Axis::Z);
  JTX::Util::Mat4 rot_x =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(15.0f), JTX::Util::Axis::X);
  JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(JTX::Util::degToRad(-60.0f),
                                                    JTX::Util::Axis::Y);
  JTX::Util::Mat4 trans = JTX::Util::Mat4::translation(0.0f, -1.0f, 0.0f);

  m.applyTransform(&scale);
  m.applyTransform(&rot_y);
  m.applyTransform(&rot_x);
  m.applyTransform(&trans);
  m.applyTransform(&rot_z);

  m.calculateNormals();
  JTX::Util::Vec3f pos{0.0f, 0.0f, 30.0f};
  JTX::Util::Vec3f target{0.0f, 0.0f, 0.0f};
  JTX::Util::Vec3f up{0.0f, 1.0f, 0.0f};
  JTX::Core::Camera cam(pos, target, up, 1.0472f, 0.1f, 100.0f);

  JTX::Core::DirLight light({0.0f, 0.0f, -1.0f}, 1.0f);

  JTX::Core::Scene scene{cam};
  scene.addPrimitive(m);
  scene.addLight(light);

  r.render(&scene);
  r.saveFb("persp_stress_test.png", 0);
}