find_package(Catch2 CONFIG REQUIRED)

add_executable(Tests test_vec3.cpp
        test_vec2.cpp
        test_vec4.cpp
        tconstants.h
        tconstants.h
        test_ray.cpp
        test_bb.cpp
        test_spherical.cpp
)

target_link_libraries(Tests PRIVATE JTXLib Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(Tests)