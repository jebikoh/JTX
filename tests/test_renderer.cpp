//
// Created by Jayden Edara on 4/3/24.
//
#include "JTX/core/core.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

const std::string CUBE_PATH = "../../Tests/primitives/cube.obj";

TEST_CASE("Renderer drawPixel()/getPixel()", "[Renderer]") {
  JTX::Core::Renderer r(100, 100, nullptr, 3);
  r.drawPixel(50, 50, 1.0f, 0.5f, 0.25f);
  REQUIRE(r.getPixel(50, 50, 0) == 1.0f);
  REQUIRE(r.getPixel(50, 50, 1) == 0.5f);
  REQUIRE(r.getPixel(50, 50, 2) == 0.25f);
}

TEST_CASE("Renderer clear() fb and zb", "[Renderer]") {
  JTX::Core::Renderer r(100, 100, nullptr, 3);
  r.drawPixel(50, 50, 0, 0.0f);
  r.clear();
  REQUIRE(r.getPixel(50, 50, 0) == 0.0f);
}

TEST_CASE("Renderer drawLine() straight diagonal", "[Renderer]") {
  JTX::Core::Renderer r(10, 10, nullptr, 3);
  r.drawLine(4, 4, 6, 6, 1.0f, 0.0f, 0.0f);
  REQUIRE(r.getPixel(4, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(5, 5, 0) == 1.0f);
  REQUIRE(r.getPixel(6, 6, 0) == 1.0f);
}

TEST_CASE("Renderer drawLine() long diagonal", "[Renderer]") {
  JTX::Core::Renderer r(10, 10, nullptr, 3);
  r.drawLine(2, 4, 8, 6, 1.0f, 0.0f, 0.0f);
  REQUIRE(r.getPixel(2, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(3, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 5, 0) == 1.0f);
  REQUIRE(r.getPixel(5, 5, 0) == 1.0f);
  REQUIRE(r.getPixel(6, 5, 0) == 1.0f);
  REQUIRE(r.getPixel(7, 6, 0) == 1.0f);
  REQUIRE(r.getPixel(8, 6, 0) == 1.0f);
}

TEST_CASE("Renderer drawLine() horizontal", "[Renderer]") {
  JTX::Core::Renderer r(10, 10, nullptr, 3);
  r.drawLine(2, 4, 8, 4, 1.0f, 0.0f, 0.0f);
  REQUIRE(r.getPixel(2, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(3, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(5, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(6, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(7, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(8, 4, 0) == 1.0f);
}

TEST_CASE("Renderer drawLine() vertical", "[Renderer]") {
  JTX::Core::Renderer r(10, 10, nullptr, 3);
  r.drawLine(4, 2, 4, 8, 1.0f, 0.0f, 0.0f);
  REQUIRE(r.getPixel(4, 2, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 3, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 5, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 6, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 7, 0) == 1.0f);
  REQUIRE(r.getPixel(4, 8, 0) == 1.0f);
}

TEST_CASE("Renderer drawLine() with color struct") {
  JTX::Core::Renderer r(10, 10, nullptr, 3);
  JTX::Util::Color red = {1.0f, 0.0f, 0.0f};
  r.drawLine(4, 4, 6, 6, red);
  REQUIRE(r.getPixel(4, 4, 0) == 1.0f);
  REQUIRE(r.getPixel(5, 5, 0) == 1.0f);
  REQUIRE(r.getPixel(6, 6, 0) == 1.0f);
}

TEST_CASE("Renderer drawTriangle()", "[Renderer]") {
  JTX::Core::Renderer r(10, 10, nullptr, 3);
  r.drawTriangle({2, 2}, 1.0f, {8, 2}, 1.0f, {5, 8}, 1.0f, 255.0f, 0.0f, 0.0f);
  REQUIRE(r.getPixel(2, 2, 0) == 255.0f);
  REQUIRE(r.getPixel(3, 2, 0) == 255.0f);
  REQUIRE(r.getPixel(4, 2, 0) == 255.0f);
  REQUIRE(r.getPixel(5, 2, 0) == 255.0f);
  REQUIRE(r.getPixel(6, 2, 0) == 255.0f);
  REQUIRE(r.getPixel(7, 2, 0) == 255.0f);
  REQUIRE(r.getPixel(8, 2, 0) == 255.0f);
  REQUIRE(r.getPixel(2, 2, 1) == 0.0f);
  REQUIRE(r.getPixel(3, 2, 1) == 0.0f);
  REQUIRE(r.getPixel(4, 2, 1) == 0.0f);
  REQUIRE(r.getPixel(5, 2, 1) == 0.0f);
  REQUIRE(r.getPixel(6, 2, 1) == 0.0f);
  REQUIRE(r.getPixel(7, 2, 1) == 0.0f);
  REQUIRE(r.getPixel(8, 2, 1) == 0.0f);
}