// These tests (more like samples) are for visual inspection.

#include "JTX/core/core.hpp"
#include "JTX/util/util.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>

static const std::string CUBE_PATH = "../../Tests/primitives/cube.obj";
static const std::string HEAD_PATH = "../../Tests/primitives/head.obj";
static const std::string GT3_PATH = "../../Tests/primitives/gt3rs.obj";

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
  r.drawTriangle(300, 300, 0.0f, 700, 300, 0.0f, 500, 700, 0.0f,
                 JTX::Util::WHITE);
  r.saveFb("triangle.png", 0);
}

TEST_CASE("Random color head", "[SaveFB]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1000, 1000, &shader, 3);
  JTX::Core::Primitive m{};
  m.load(HEAD_PATH);

  JTX::Util::Vec3 lookAt = {0.0f, 0.0f, -1.0f};

  JTX::Util::Mat4 rot_z =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(180), JTX::Util::Axis::Z);
  JTX::Util::Mat4 scale2 = JTX::Util::Mat4::scale(499.0f, 499.0f, 1);
  JTX::Util::Mat4 trans = JTX::Util::Mat4::translation(500.0f, 500.0f, 0);

  m.applyTransform(&rot_z);
  m.applyTransform(&scale2);
  m.applyTransform(&trans);
  m.calculateNormals();

  for (int i = 0; i < m.getNumFaces(); i++) {
    if (lookAt.dot(m.getNormal(i)[0], m.getNormal(i)[1], m.getNormal(i)[2]) >=
        0) {
      continue;
    }

    JTX::Core::Face *f = m.getFace(i);
    float *v1 = m.getVertex(f->v1);
    float *v2 = m.getVertex(f->v2);
    float *v3 = m.getVertex(f->v3);

    int v1_x = static_cast<int>(std::round(v1[0]));
    int v1_y = static_cast<int>(std::round(v1[1]));
    int v2_x = static_cast<int>(std::round(v2[0]));
    int v2_y = static_cast<int>(std::round(v2[1]));
    int v3_x = static_cast<int>(std::round(v3[0]));
    int v3_y = static_cast<int>(std::round(v3[1]));

    JTX::Util::Color color = {static_cast<float>(rand() % 255),
                              static_cast<float>(rand() % 255),
                              static_cast<float>(rand() % 255)};

    r.drawTriangle(v1_x, v1_y, 0.0f, v2_x, v2_y, 0.0f, v3_x, v3_y, 0.0f, color);
  }
  r.saveFb("rc_head.png", 0);
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

  JTX::Util::Vec3 pos{0.0f, 0.0f, 100.0f};
  JTX::Util::Vec3 target{0.0f, 0.0f, 0.0f};
  JTX::Util::Vec3 up{0.0f, 1.0f, 0.0f};
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

  JTX::Util::Vec3 pos{0.0f, 0.0f, 30.0f};
  JTX::Util::Vec3 target{0.0f, 0.0f, 0.0f};
  JTX::Util::Vec3 up{0.0f, 1.0f, 0.0f};
  JTX::Core::Camera cam(pos, target, up, 1.0472f, 0.1f, 100.0f);

  JTX::Core::DirLight light({0.0f, 0.0f, -1.0f}, 1.0f);

  JTX::Core::Scene scene{cam};
  scene.addPrimitive(m);
  scene.addLight(light);

  r.render(&scene);
  r.saveFb("cube_perspective.png", 0);
}

TEST_CASE("Perspective projection stress test", "[Stress]") {
  JTX::Core::DefaultShader shader{};
  JTX::Core::Renderer r(1920, 1080, &shader, 3);

  JTX::Core::Primitive m{};
  m.load(GT3_PATH);
  std::cout << m.getVertex(0)[0] << ", " << m.getVertex(0)[1] << ", "
            << m.getVertex(0)[2] << std::endl;

  JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(7.0f, 7.0f, 7.0f);
  JTX::Util::Mat4 rot_x =
      JTX::Util::Mat4::rotation(JTX::Util::degToRad(15.0f), JTX::Util::Axis::X);
  JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(JTX::Util::degToRad(-60.0f),
                                                    JTX::Util::Axis::Y);
  JTX::Util::Mat4 trans = JTX::Util::Mat4::translation(0.0f, -1.0f, 0.0f);

  m.applyTransform(&scale);
  std::cout << m.getVertex(0)[0] << ", " << m.getVertex(0)[1] << ", "
            << m.getVertex(0)[2] << std::endl;
  m.applyTransform(&rot_y);
  std::cout << m.getVertex(0)[0] << ", " << m.getVertex(0)[1] << ", "
            << m.getVertex(0)[2] << std::endl;
  m.applyTransform(&rot_x);
  std::cout << m.getVertex(0)[0] << ", " << m.getVertex(0)[1] << ", "
            << m.getVertex(0)[2] << std::endl;
  m.applyTransform(&trans);
  std::cout << m.getVertex(0)[0] << ", " << m.getVertex(0)[1] << ", "
            << m.getVertex(0)[2] << std::endl;

  m.calculateNormals();
  JTX::Util::Vec3 pos{0.0f, 0.0f, 30.0f};
  JTX::Util::Vec3 target{0.0f, 0.0f, 0.0f};
  JTX::Util::Vec3 up{0.0f, 1.0f, 0.0f};
  JTX::Core::Camera cam(pos, target, up, 1.0472f, 0.1f, 100.0f);

  JTX::Core::DirLight light({0.0f, 0.0f, -1.0f}, 1.0f);

  JTX::Core::Scene scene{cam};
  scene.addPrimitive(m);
  scene.addLight(light);

  r.render(&scene);
  r.saveFb("persp_stress_test.png", 0);
}