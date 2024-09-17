cmake_minimum_required(VERSION 3.27)
project(JTX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/jtxlib)

add_executable(JTX src/main.cpp
        src/spectrum.hpp)

target_link_libraries(JTX PRIVATE jtxlib)
target_include_directories(JTX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/jtxlib/src)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(JTX PRIVATE DEBUG_ASSERT)
elseif (CMAKE_BUILD_TYPE STREQUAL "Test")
    target_compile_definitions(JTX PRIVATE TEST_ASSERT)
endif ()