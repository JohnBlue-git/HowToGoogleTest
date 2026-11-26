#include "temperature_monitor.h"

#include <gtest/gtest.h>
#include <utility>

TEST(CppBasicsTest, ComparesValues)
{
    EXPECT_EQ(2 + 3, 5);
    EXPECT_TRUE(5 > 0);
}

class TemperatureConversionTest
    : public ::testing::TestWithParam<std::pair<int, int>> {};

TEST_P(TemperatureConversionTest, ConvertsCelsiusToFahrenheit)
{
    const auto [celsius, expectedFahrenheit] = GetParam();
    EXPECT_EQ(celsiusToFahrenheit(celsius), expectedFahrenheit);
}

INSTANTIATE_TEST_SUITE_P(
    CommonTemperatures,
    TemperatureConversionTest,
    ::testing::Values(
        std::pair{-40, -40},
        std::pair{0, 32},
        std::pair{20, 68},
        std::pair{100, 212}));
