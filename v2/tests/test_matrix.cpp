#include "../src/util/matrix.hpp"
#include "tconstants.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Mat4 default constructor is identity matrix", "[BB3]") {
    jtx::Mat4 mat{};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            REQUIRE(mat[i][j] == (i == j ? 1.0f : 0.0f));
    }
    
    bool is_identity = mat.isIdentity();
    REQUIRE(is_identity);
}