//
// Created by Jayden Edara on 4/3/24.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "JTX/core/core.h"

const std::string CUBE_PATH = "../../Tests/primitives/cube.obj";

TEST_CASE("Primitive loads mesh from .obj file", "[Primitive]") {
    JTX::Core::Primitive p;
    p.load(CUBE_PATH);

    REQUIRE(p.getNumVertices() == 8);
    REQUIRE(p.getNumFaces() == 12);

    REQUIRE_THAT(p.getVertex(0)[0], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(0)[1], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(0)[2], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(1)[0], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(1)[1], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(1)[2], Catch::Matchers::WithinAbs(1.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(2)[0], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(2)[1], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(2)[2], Catch::Matchers::WithinAbs(1.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(3)[0], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(3)[1], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(3)[2], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(4)[0], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(4)[1], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(4)[2], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(5)[0], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(5)[1], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(5)[2], Catch::Matchers::WithinAbs(1.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(6)[0], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(6)[1], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(6)[2], Catch::Matchers::WithinAbs(1.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(7)[0], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(7)[1], Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(7)[2], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));

    REQUIRE(p.getFace(0)->v1 == 1);
    REQUIRE(p.getFace(0)->v2 == 2);
    REQUIRE(p.getFace(0)->v3 == 3);

    REQUIRE(p.getFace(11)->v1 == 4);
    REQUIRE(p.getFace(11)->v2 == 0);
    REQUIRE(p.getFace(11)->v3 == 7);
}

TEST_CASE("Primitive normal calculations", "[Primitive]") {
    JTX::Core::Primitive p;
    p.load(CUBE_PATH);
    p.calculateNormals();

    REQUIRE_THAT(p.getNormal(0)[0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(p.getNormal(0)[1], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
    REQUIRE_THAT(p.getNormal(0)[2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(p.getNormal(p.getNumFaces() - 1)[0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(p.getNormal(p.getNumFaces() - 1)[1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(p.getNormal(p.getNumFaces() - 1)[2], Catch::Matchers::WithinAbs(-1.0f, 0.0001f));
}

TEST_CASE("Test cube rotation XY", "[Primitive]") {
    JTX::Core::Primitive p;
    p.load(CUBE_PATH);

    float rad = JTX::Util::degToRad(45);
    JTX::Util::Mat4 rot_x = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);
    JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);

    p.applyTransform(&rot_x);
    p.applyTransform(&rot_y);

    float *v0 = p.getVertex(0);

    REQUIRE_THAT(v0[0], Catch::Matchers::WithinAbs(-0.292893219f, 0.0001f));
    REQUIRE_THAT(v0[1], Catch::Matchers::WithinAbs(0.000f, 0.0001f));
    REQUIRE_THAT(v0[2], Catch::Matchers::WithinAbs(-1.70710678f, 0.0001f));
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

    std::cout << p.getNormal(3)[0] << " " << p.getNormal(3)[1] << " " << p.getNormal(3)[2] << std::endl;

    REQUIRE_THAT(p.getNormal(0)[0], Catch::Matchers::WithinAbs(-0.5000f, 0.0001f));
    REQUIRE_THAT(p.getNormal(0)[1], Catch::Matchers::WithinAbs(-0.707106781f, 0.0001f));
    REQUIRE_THAT(p.getNormal(0)[2], Catch::Matchers::WithinAbs(-0.5f, 0.0001f));
}

TEST_CASE("Apply scale transformation to cube primitive", "[Primitive]") {
    JTX::Core::Primitive p;
    p.load(CUBE_PATH);

    JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(2.0f, 2.0f, 2.0f);
    p.applyTransform(&scale);

    REQUIRE_THAT(p.getVertex(0)[0], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(0)[1], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(0)[2], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(1)[0], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(1)[1], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(1)[2], Catch::Matchers::WithinAbs(2.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(2)[0], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(2)[1], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(2)[2], Catch::Matchers::WithinAbs(2.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(3)[0], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(3)[1], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(3)[2], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(4)[0], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(4)[1], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(4)[2], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(5)[0], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(5)[1], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(5)[2], Catch::Matchers::WithinAbs(2.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(6)[0], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(6)[1], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(6)[2], Catch::Matchers::WithinAbs(2.0f, 0.0001f));

    REQUIRE_THAT(p.getVertex(7)[0], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(7)[1], Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(p.getVertex(7)[2], Catch::Matchers::WithinAbs(-2.0f, 0.0001f));

    REQUIRE(p.getFace(0)->v1 == 1);
    REQUIRE(p.getFace(0)->v2 == 2);
    REQUIRE(p.getFace(0)->v3 == 3);

    REQUIRE(p.getFace(11)->v1 == 4);
    REQUIRE(p.getFace(11)->v2 == 0);
    REQUIRE(p.getFace(11)->v3 == 7);
}

TEST_CASE("Test DirLight intensity", "[Lights]") {
    JTX::Core::DirLight dl(JTX::Util::Vec3(1.0f, 1.0f, 1.0f));

    REQUIRE_THAT(dl.getIntensity(JTX::Util::Vec3(-1.0f, -1.0f, -1.0f)), Catch::Matchers::WithinAbs(1.7320508075688776f, 0.0001f));
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

    JTX::Core::DirLight dl(JTX::Util::Vec3(0.0f, 0.0f, -1.0f));

    float *normal = p.getNormal(3);
    float intensity = dl.getIntensity({normal[0], normal[1], normal[2]});
    std::cout << intensity << std::endl;
}

TEST_CASE("Test camera constructor", "[Camera]") {
    JTX::Core::Camera cam(JTX::Util::Vec3(0.0f, 0.0f, 30.0f), JTX::Util::Vec3(0.0f, 0.0f, 0.0f), JTX::Util::Vec3(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);

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
    JTX::Core::Camera cam(JTX::Util::Vec3(0.0f, 0.0f, 30.0f), JTX::Util::Vec3(0.0f, 0.0f, 0.0f), JTX::Util::Vec3(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);

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
    JTX::Core::Camera cam(JTX::Util::Vec3(0.0f, 0.0f, 30.0f), JTX::Util::Vec3(0.0f, 0.0f, 0.0f), JTX::Util::Vec3(0.0f, 1.0f, 0.0f), 1.0472f, 0.1f, 100.0f);

    auto pmat = cam.getProjMatrix(2.0f, JTX::Core::PERSPECTIVE);
    REQUIRE_THAT(pmat.data[0][0], Catch::Matchers::WithinAbs(0.86602295, 0.0001f));
    REQUIRE_THAT(pmat.data[0][1], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(pmat.data[0][2], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(pmat.data[0][3], Catch::Matchers::WithinAbs(0.0f, 0.0001f));

    REQUIRE_THAT(pmat.data[1][0], Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(pmat.data[1][1], Catch::Matchers::WithinAbs(1.73204591, 0.0001f));
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
    JTX::Core::Camera cam(JTX::Util::Vec3(0.0f, 0.0f, 30.0f),
                          JTX::Util::Vec3(0.0f, 0.0f, 0.0f),
                          JTX::Util::Vec3(0.0f, 1.0f, 0.0f),
                          1.0472f,
                          0.1f,
                          100.0f);
    JTX::Core::Scene scene(cam);
    JTX::Core::Primitive p;
    p.load(CUBE_PATH);
    JTX::Core::DirLight dl(JTX::Util::Vec3(1.0f, 1.0f, 1.0f));
    auto cube = scene.addLight(dl);
    auto l = scene.addPrimitive(p);

    REQUIRE(scene.getNumPrimitives() == 1);
    REQUIRE(scene.getNumLights() == 1);

    REQUIRE(scene.getPrimitive(cube).getNumVertices() == 8);
    REQUIRE(scene.getPrimitive(l).getNumFaces() == 12);

    JTX::Util::Vec3 pos = scene.getCamera().getPos();

    REQUIRE(pos.x == 0.0f);
    REQUIRE(pos.y == 0.0f);
    REQUIRE(pos.z == 30.0f);
}

TEST_CASE("Test scene remove primitive and dirlight", "[Scene]") {
    JTX::Core::Camera cam(JTX::Util::Vec3(0.0f, 0.0f, 30.0f),
                          JTX::Util::Vec3(0.0f, 0.0f, 0.0f),
                          JTX::Util::Vec3(0.0f, 1.0f, 0.0f),
                          1.0472f,
                          0.1f,
                          100.0f);
    JTX::Core::Scene scene(cam);
    JTX::Core::Primitive p;
    p.load(CUBE_PATH);
    JTX::Core::DirLight dl(JTX::Util::Vec3(1.0f, 1.0f, 1.0f));
    auto cube = scene.addLight(dl);
    auto l = scene.addPrimitive(p);

    scene.removePrimitive(l);
    scene.removeLight(cube);

    REQUIRE(scene.getNumPrimitives() == 0);
    REQUIRE(scene.getNumLights() == 0);
}
