add_library(temperature_monitor src/temperature_monitor.cpp)
target_include_directories(temperature_monitor PUBLIC include)
target_link_libraries(temperature_monitor PUBLIC GTest::gtest)

add_executable(
    cpp_demo_tests
    tests/basics_test.cpp
    tests/private_member_test.cpp
    tests/temperature_monitor_test.cpp
)
target_link_libraries(cpp_demo_tests PRIVATE temperature_monitor GTest::gtest_main GTest::gmock)

include(GoogleTest)
gtest_discover_tests(cpp_demo_tests)
