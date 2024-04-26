// These tests (more like samples) are for visual inspection.

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "JTX/core/core.h"
#include "JTX/util/util.h"
#include <iostream>

const std::string CUBE_PATH = "../../Tests/primitives/cube.obj";
const std::string HEAD_PATH = "../../Tests/primitives/head.obj";
const JTX::Util::Color WHITE = {1.0f, 1.0f, 1.0f};


TEST_CASE("Renderer saveFb() with vertical line", "[SaveFB]") {
    JTX::Core::Renderer r(1000, 1000, 3);
    r.drawLine(500, 0, 500, 999, WHITE);
    r.drawLine(0, 500, 999, 500, WHITE);
    r.drawLine(0, 0, 999, 999, WHITE);
    r.drawLine(0, 999, 999, 0, WHITE);
    r.saveFb("vertical_line.png", 0);
}

TEST_CASE("Cube wireframe", "[SaveFB]") {
    JTX::Core::Renderer r(1000, 1000, 3);
    JTX::Core::Primitive m{};
    m.load(CUBE_PATH);

    float rad = JTX::Util::degToRad(45);
    JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);
    JTX::Util::Mat4 rot_z = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);
    JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(0.5, 0.5, 0.5);

    m.applyTransform(&rot_y);
    m.applyTransform(&rot_z);
    m.applyTransform(&scale);

    r.renderWireframe(m, WHITE);
    r.saveFb("cube_wireframe.png", 0);
}

TEST_CASE("Head wireframe", "[SaveFB]") {
    JTX::Core::Renderer r(1000, 1000, 3);
    JTX::Core::Primitive m{};
    m.load(HEAD_PATH);

    JTX::Util::Mat4 rot_z = JTX::Util::Mat4::rotation(JTX::Util::degToRad(180), JTX::Util::Axis::Z);

    m.applyTransform(&rot_z);
    r.renderWireframe(m, WHITE);
    r.saveFb("head_wireframe.png", 0);
}