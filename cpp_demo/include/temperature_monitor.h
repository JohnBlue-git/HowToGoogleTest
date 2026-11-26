#ifndef HOW_TO_GOOGLE_TEST_TEMPERATURE_MONITOR_H
#define HOW_TO_GOOGLE_TEST_TEMPERATURE_MONITOR_H

#include <gtest/gtest_prod.h>

int celsiusToFahrenheit(int celsius);

class TemperatureMonitor {
public:
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void onHighTemperature(int temperature) = 0;
    };

    explicit TemperatureMonitor(Observer &observer, int threshold);
    void record(int temperature);

private:
    static int normalizeForDisplay(int temperature);

    Observer &observer_;
    int threshold_;

    FRIEND_TEST(PrivateMemberTest, NormalizeClampsNegativeValues);
};

#endif
