#include "temperature_monitor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::StrictMock;

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
