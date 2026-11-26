#include "temperature_input.h"

#include <charconv>
#include <stdexcept>
#include <system_error>

int parseCelsius(std::string_view input)
{
    if (input.empty()) {
        throw std::invalid_argument("temperature must be an integer");
    }

    int temperature = 0;
    const char *begin = input.data();
    const char *end = begin + input.size();
    const auto [parsedEnd, error] = std::from_chars(begin, end, temperature);

    if (error != std::errc{} || parsedEnd != end) {
        throw std::invalid_argument("temperature must be an integer");
    }

    return temperature;
}
