#include "temperature_monitor.h"

#include <gtest/gtest.h>

using TemperatureNumberTypes = ::testing::Types<int, long, double>;

template <typename Number>
class TemperatureConversionTypedTest : public ::testing::Test {};

TYPED_TEST_SUITE(TemperatureConversionTypedTest, TemperatureNumberTypes);

TYPED_TEST(TemperatureConversionTypedTest, ConvertsForSupportedNumberTypes)
{
    const TypeParam celsius{20};
    const TypeParam expectedFahrenheit{68};

    EXPECT_EQ(celsiusToFahrenheit(celsius), expectedFahrenheit);
}
