#include "temperature_monitor.h"

#include <gtest/gtest.h>

TEST(PrivateMemberTest, NormalizeClampsNegativeValues)
{
    EXPECT_EQ(TemperatureMonitor::normalizeForDisplay(-5), 0);
    EXPECT_EQ(TemperatureMonitor::normalizeForDisplay(5), 5);
}
