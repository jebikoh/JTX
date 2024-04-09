cmake_minimum_required(VERSION 3.27)
project(JTX)

set(CMAKE_CXX_STANDARD 17)
set(CBLAS_DIR /opt/homebrew/opt/openblas)

include_directories(${CBLAS_DIR}/include/)
link_directories(${CBLAS_DIR}/lib/)

add_library(JTX
        JTX/Util/Util.h
        JTX/Util/Vec3.h
        JTX/Util/Mat4.cpp
        JTX/Util/Mat4.h
        JTX/Core/Primitive.cpp
        JTX/Core/Primitive.h
        JTX/Core/Core.h
        JTX/Core/Lights.h
        JTX/Core/Scene.cpp
        JTX/Core/Scene.h
        JTX/Core/Camera.h
)

target_include_directories(JTX PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(JTX openblas)

add_subdirectory(Tests)
