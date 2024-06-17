#include "../src/util/bounds.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("BB3f default constructor", "[BB3]") {
    jtx::BB3f bb;
    REQUIRE(bb.pmin.x == std::numeric_limits<float>::max());
    REQUIRE(bb.pmin.y == std::numeric_limits<float>::max());
    REQUIRE(bb.pmin.z == std::numeric_limits<float>::max());
    REQUIRE(bb.pmax.x == std::numeric_limits<float>::lowest());
    REQUIRE(bb.pmax.y == std::numeric_limits<float>::lowest());
    REQUIRE(bb.pmax.z == std::numeric_limits<float>::lowest());
}

TEST_CASE("BB3f constructor with 2 points", "[BB3]") {
    jtx::Point3f pmin(1.0f, 8.0f, 3.0f);
    jtx::Point3f pmax(4.0f, 5.0f, 6.0f);
    jtx::BB3f bb(pmin, pmax);
    REQUIRE(bb.pmin == jtx::Point3f{1.0f, 5.0f, 3.0f});
    REQUIRE(bb.pmax == jtx::Point3f{4.0f, 8.0f, 6.0f});
}

TEST_CASE("BB3f constructor with 1 point", "[BB3]") {
    jtx::Point3f p(1.0f, 2.0f, 3.0f);
    jtx::BB3f bb(p);
    REQUIRE(bb.pmin == p);
    REQUIRE(bb.pmax == p);
}

TEST_CASE("BB3f copy constructor", "[BB3]") {
    jtx::Point3f pmin(1.0f, 8.0f, 3.0f);
    jtx::Point3f pmax(4.0f, 5.0f, 6.0f);
    jtx::BB3f bb(pmin, pmax);
    jtx::BB3f bbCopy(bb);
    REQUIRE(bbCopy.pmin == jtx::Point3f{1.0f, 5.0f, 3.0f});
    REQUIRE(bbCopy.pmax == jtx::Point3f{4.0f, 8.0f, 6.0f});
}

TEST_CASE("BB3f copy constructor (empty)", "[BB3]") {
    jtx::BB3f bb;
    bb.pmin = jtx::Point3f{1.0f, 1.0f, 1.0f};
    bb.pmax = jtx::Point3f{0.0f, 0.0f, 0.0f};
    jtx::BB3f bb2(bb);
    jtx::BB3f ref = jtx::BB3f();
    REQUIRE(bb2.pmin == ref.pmin);
    REQUIRE(bb2.pmax == ref.pmax);
}

//region isEmpty() / isDegenerate()
TEST_CASE("BB3f isEmpty (true)", "[BB3]") {
    jtx::BB3f bb;
    bb.pmax = jtx::Point3f{1.0f, 1.0f, 1.0f};
    bb.pmin = jtx::Point3f{2.0f, 2.0f, 2.0f};
    REQUIRE(bb.isEmpty() == true);
}

TEST_CASE("BB3f isEmpty (false)", "[BB3]") {
    jtx::BB3f bb;
    bb.pmax = jtx::Point3f{2.0f, 2.0f, 2.0f};
    bb.pmin = jtx::Point3f{1.0f, 1.0f, 1.0f};
    REQUIRE(bb.isEmpty() == false);
}

TEST_CASE("BB3f isEmpty (one-dim, true)", "[BB3]") {
    jtx::BB3f bb;
    bb.pmax = jtx::Point3f{1.0f, 2.0f, 2.0f};
    bb.pmin = jtx::Point3f{1.0f, 1.0f, 1.0f};
    REQUIRE(bb.isEmpty() == true);
}

TEST_CASE("BB3f isDegenerate (true)", "[BB3]") {
    jtx::BB3f bb;
    bb.pmax = jtx::Point3f{1.0f, 1.0f, 1.0f};
    bb.pmin = jtx::Point3f{2.0f, 2.0f, 2.0f};
    REQUIRE(bb.isDegenerate() == true);
}

TEST_CASE("BB3f isDegenerate (false)", "[BB3]") {
    jtx::BB3f bb;
    bb.pmax = jtx::Point3f{3.0f, 3.0f, 3.0f};
    bb.pmin = jtx::Point3f{2.0f, 2.0f, 2.0f};
    REQUIRE(bb.isDegenerate() == false);
}
//endregion