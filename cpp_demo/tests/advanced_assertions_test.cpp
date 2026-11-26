#include "temperature_input.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {

void failFastOnNegativeTemperature(int temperature)
{
    if (temperature < 0) {
        std::cerr << "negative temperature";
        std::abort();
    }
}

}

TEST(AdvancedAssertionsTest, ThrowsForInvalidTemperatureText)
{
    EXPECT_EQ(parseCelsius("21"), 21);
    EXPECT_THROW(parseCelsius("21C"), std::invalid_argument);
    EXPECT_THROW(parseCelsius(""), std::invalid_argument);
}

TEST(AdvancedAssertionsTest, DeathTestChecksFailFastBehavior)
{
    EXPECT_DEATH(failFastOnNegativeTemperature(-1), "negative temperature");
}
