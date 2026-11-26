add_library(c_calculator src/calculator.c)
target_include_directories(c_calculator PUBLIC include)

add_executable(c_demo_tests tests/calculator_test.cpp)
target_link_libraries(c_demo_tests PRIVATE c_calculator GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(c_demo_tests)
