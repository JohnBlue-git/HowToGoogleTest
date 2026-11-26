#ifndef HOW_TO_GOOGLE_TEST_CALCULATOR_H
#define HOW_TO_GOOGLE_TEST_CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum CalculatorStatus {
    CALCULATOR_OK = 0,
    CALCULATOR_DIVIDE_BY_ZERO,
    CALCULATOR_INVALID_ARGUMENT
} CalculatorStatus;

int calculator_add(int left, int right);
CalculatorStatus calculator_divide(int dividend, int divisor, int *result);

#ifdef __cplusplus
}
#endif

#endif
