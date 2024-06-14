find_package(Catch2 CONFIG REQUIRED)

add_executable(Tests test_vector.cpp)

target_link_libraries(Tests PRIVATE JTXLib Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(Tests)