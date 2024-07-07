cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 20)

project(JTX)

# Build flags
if (CMAKE_BUILD_TYPE STREQUAL "Test")
    add_definitions(-DJTX_TEST)
else (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DJTX_NDEBUG)
endif ()

# Catch2
add_subdirectory("lib/Catch2")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/extras)
include(CTest)
include(Catch)

# Subdirectories
add_subdirectory("src")
add_subdirectory("tests")

