add_executable(tests
        test_vec3.cpp
        test_vec2.cpp
        test_vec4.cpp
        test_ray.cpp
        test_bbox.cpp
        test_spherical.cpp
        test_mat4.cpp
)

target_link_libraries(tests PRIVATE jtxlib Catch2WithMain)

catch_discover_tests(tests)