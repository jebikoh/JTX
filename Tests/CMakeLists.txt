find_package(Catch2 3 REQUIRED)
add_executable(Tests TestUtil.cpp
        TestCore.cpp)

target_link_libraries(Tests PRIVATE JTX)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(Tests)

