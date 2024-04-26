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

    JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(150, 150, 1);
    JTX::Util::Mat4 trans = JTX::Util::Mat4::translation(500, 500, 0);

    float rad = JTX::Util::degToRad(45);
    JTX::Util::Mat4 rot_y = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::Y);
    JTX::Util::Mat4 rot_z = JTX::Util::Mat4::rotation(rad, JTX::Util::Axis::X);

    m.applyTransform(&rot_y);
    m.applyTransform(&rot_z);
    m.applyTransform(&scale);
    m.applyTransform(&trans);

    for (int i = 0; i < m.getNumFaces(); i++) {
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

        r.drawLine(v1_x, v1_y, v2_x, v2_y, WHITE);
        r.drawLine(v2_x, v2_y, v3_x, v3_y, WHITE);
        r.drawLine(v3_x, v3_y, v1_x, v1_y, WHITE);
    }
    r.saveFb("cube_wireframe.png", 0);
}

TEST_CASE("Head wireframe", "[SaveFB]") {
    JTX::Core::Renderer r(1000, 1000, 3);
    JTX::Core::Primitive m{};
    m.load(HEAD_PATH);

    JTX::Util::Mat4 scale = JTX::Util::Mat4::scale(499, 499, 1);
    JTX::Util::Mat4 trans = JTX::Util::Mat4::translation(500, 500, 0);
    JTX::Util::Mat4 rot_z = JTX::Util::Mat4::rotation(JTX::Util::degToRad(180), JTX::Util::Axis::Z);

    m.applyTransform(&rot_z);
    m.applyTransform(&scale);
    m.applyTransform(&trans);

    for (int i = 0; i < m.getNumFaces(); i++) {
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

        r.drawLine(v1_x, v1_y, v2_x, v2_y, WHITE);
        r.drawLine(v2_x, v2_y, v3_x, v3_y, WHITE);
        r.drawLine(v3_x, v3_y, v1_x, v1_y, WHITE);
    }
    r.saveFb("head_wireframe.png", 0);
}