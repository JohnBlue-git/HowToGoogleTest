#include "calculator.h"

int calculator_add(int left, int right)
{
    return left + right;
}

CalculatorStatus calculator_divide(int dividend, int divisor, int *result)
{
    if (result == 0) {
        return CALCULATOR_INVALID_ARGUMENT;
    }

    if (divisor == 0) {
        return CALCULATOR_DIVIDE_BY_ZERO;
    }

    *result = dividend / divisor;
    return CALCULATOR_OK;
}
