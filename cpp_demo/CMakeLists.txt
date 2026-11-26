add_library(temperature_monitor
    src/temperature_input.cpp
    src/temperature_monitor.cpp
)
target_include_directories(temperature_monitor PUBLIC include)
target_link_libraries(temperature_monitor PUBLIC GTest::gtest)

add_executable(
    cpp_demo_tests
    tests/basics_test.cpp
    tests/advanced_assertions_test.cpp
    tests/fixture_lifecycle_test.cpp
    tests/private_member_test.cpp
    tests/temperature_monitor_test.cpp
    tests/temperature_types_test.cpp
    tests/test_main.cpp
)
target_link_libraries(cpp_demo_tests PRIVATE temperature_monitor GTest::gtest GTest::gmock)

include(GoogleTest)
gtest_discover_tests(cpp_demo_tests)
