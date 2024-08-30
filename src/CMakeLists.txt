add_library(jtxlib util/constants.hpp
        util/numerical.hpp
        util/vec2.hpp
        util/vec3.hpp
        util/vec4.hpp
        util/assert.hpp
        util/matrix.hpp
        util/matrix.cpp
        util/math.hpp
        util/vecmath.hpp
        util/ray.hpp
        util/bounds.hpp
        util/spherical.hpp
        util/transform.hpp
)
target_include_directories(jtxlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/util)

add_executable (jtx "main.cpp")
target_link_libraries(jtx PRIVATE jtxlib)