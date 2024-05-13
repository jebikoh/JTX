cmake_minimum_required(VERSION 3.27)
project(JTX)

set(CMAKE_CXX_STANDARD 17)
set(CBLAS_DIR /opt/homebrew/opt/openblas)

include_directories(${CBLAS_DIR}/include/)
link_directories(${CBLAS_DIR}/lib/)

add_library(JTX
        JTX/util/util.hpp
        JTX/util/vec3.hpp
        JTX/util/mat4.cpp
        JTX/util/mat4.hpp
        JTX/core/primitive.cpp
        JTX/core/primitive.hpp
        JTX/core/core.hpp
        JTX/core/lights.hpp
        JTX/core/scene.hpp
        JTX/core/camera.hpp
        JTX/core/renderer.cpp
        JTX/core/renderer.hpp
)

add_library(fpng STATIC external/fpng.cpp)
target_include_directories(fpng PRIVATE external)

target_include_directories(JTX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(JTX PRIVATE openblas fpng)

add_subdirectory(tests)
