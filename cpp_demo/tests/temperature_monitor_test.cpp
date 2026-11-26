#include "temperature_monitor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::InSequence;
using ::testing::SaveArg;
using ::testing::StrictMock;

MATCHER_P(AtLeastTemperature, threshold, "is at least the threshold")
{
    return arg >= threshold;
}

class MockTemperatureObserver : public TemperatureMonitor::Observer {
public:
    MOCK_METHOD(void, onHighTemperature, (int temperature), (override));
};

class TemperatureMonitorTest : public ::testing::Test {
protected:
    StrictMock<MockTemperatureObserver> observer;
    TemperatureMonitor monitor{observer, 30};
};

TEST_F(TemperatureMonitorTest, NotifiesObserverAtTheThreshold)
{
    EXPECT_CALL(observer, onHighTemperature(30)).Times(1);

    monitor.record(30);
}

TEST_F(TemperatureMonitorTest, DoesNotNotifyBelowTheThreshold)
{
    EXPECT_CALL(observer, onHighTemperature(_)).Times(0);

    monitor.record(29);
}

TEST_F(TemperatureMonitorTest, MatchesArgumentsAndChecksCallOrder)
{
    int lastReportedTemperature = 0;
    InSequence sequence;
    EXPECT_CALL(observer, onHighTemperature(AtLeastTemperature(30)))
        .WillOnce(SaveArg<0>(&lastReportedTemperature));
    EXPECT_CALL(observer, onHighTemperature(AtLeastTemperature(30)))
        .WillOnce(SaveArg<0>(&lastReportedTemperature));

    monitor.record(30);
    monitor.record(35);

    EXPECT_EQ(lastReportedTemperature, 35);
}
