cmake_minimum_required(VERSION 3.27)
project(JTX)

set(CMAKE_CXX_STANDARD 17)
set(CBLAS_DIR /opt/homebrew/opt/openblas)

include_directories(${CBLAS_DIR}/include/)
link_directories(${CBLAS_DIR}/lib/)

add_library(JTX
        JTX/util/util.h
        JTX/util/vec3.h
        JTX/util/mat4.cpp
        JTX/util/mat4.h
        JTX/core/primitive.cpp
        JTX/core/primitive.h
        JTX/core/core.h
        JTX/core/lights.h
        JTX/core/scene.h
        JTX/core/camera.h
        JTX/core/renderer.cpp
        JTX/core/renderer.h
)

add_library(fpng STATIC external/fpng.cpp)
target_include_directories(fpng PRIVATE external)

target_include_directories(JTX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(JTX PRIVATE openblas fpng)

add_subdirectory(tests)
