#include "temperature_monitor.h"

#include <algorithm>

TemperatureMonitor::TemperatureMonitor(Observer &observer, int threshold)
    : observer_(observer), threshold_(threshold)
{
}

void TemperatureMonitor::record(int temperature)
{
    if (temperature >= threshold_) {
        observer_.onHighTemperature(temperature);
    }
}

int TemperatureMonitor::normalizeForDisplay(int temperature)
{
    return std::max(temperature, 0);
}
