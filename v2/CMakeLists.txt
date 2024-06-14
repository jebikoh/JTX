cmake_minimum_required(VERSION 3.27)
project(JTX)

set(CMAKE_CXX_STANDARD 17)

add_library(JTXLib src/util/constants.hpp
        src/util/numerical.h
        src/util/vec2.hpp
        src/util/vec3.hpp
        src/util/vec4.hpp
        src/util/assert.h
        src/util/Mat4.cpp
        src/util/Mat4.hpp)

set_target_properties(JTXLib PROPERTIES LINKER_LANGUAGE CXX)

find_package(OpenBLAS CONFIG REQUIRED)
target_link_libraries(JTXLib PRIVATE OpenBLAS::OpenBLAS)

add_executable(JTX src/main.cpp)
target_link_libraries(JTX PRIVATE JTXLib)

add_subdirectory(tests)