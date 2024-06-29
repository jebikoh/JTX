cmake_minimum_required(VERSION 3.27)
project(JTX)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Test")
    add_definitions(-DJTX_TEST)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DJTX_NDEBUG)
endif ()

add_library(JTXLib src/util/constants.hpp
        src/util/numerical.hpp
        src/util/vec2.hpp
        src/util/vec3.hpp
        src/util/vec4.hpp
        src/util/assert.hpp
        src/util/matrix.cpp
        src/util/matrix.hpp
        src/util/math.hpp
        src/util/vecmath.hpp
        src/util/ray.hpp
        src/util/bounds.hpp
        src/util/spherical.hpp)

set_target_properties(JTXLib PROPERTIES LINKER_LANGUAGE CXX)

find_package(OpenBLAS CONFIG REQUIRED)
target_link_libraries(JTXLib PRIVATE OpenBLAS::OpenBLAS)

add_executable(JTX src/main.cpp)
target_link_libraries(JTX PRIVATE JTXLib)

add_subdirectory(tests)