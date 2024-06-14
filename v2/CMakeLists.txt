cmake_minimum_required(VERSION 3.28)
project(JTX)

set(CMAKE_CXX_STANDARD 17)

add_executable(JTX src/main.cpp
        src/util/constants.hpp
        src/util/vec2.hpp
        src/util/vec3.hpp
        src/util/vec4.hpp
        src/util/assert.h
        src/util/numerical.h)

find_package(OpenBLAS CONFIG REQUIRED)
target_link_libraries(JTX PRIVATE OpenBLAS::OpenBLAS)