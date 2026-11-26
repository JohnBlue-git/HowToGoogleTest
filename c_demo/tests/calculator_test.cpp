#include "calculator.h"

#include <gtest/gtest.h>

TEST(CalculatorTest, AddsTwoIntegers)
{
    EXPECT_EQ(calculator_add(2, 3), 5);
}

TEST(CalculatorTest, DividesAndStoresTheResult)
{
    int result = 0;

    ASSERT_EQ(calculator_divide(12, 3, &result), CALCULATOR_OK);
    EXPECT_EQ(result, 4);
}

TEST(CalculatorTest, ReportsDivisionByZero)
{
    int result = 123;

    EXPECT_EQ(calculator_divide(12, 0, &result), CALCULATOR_DIVIDE_BY_ZERO);
    EXPECT_EQ(result, 123);
}

TEST(CalculatorTest, RejectsNullResultPointer)
{
    EXPECT_EQ(calculator_divide(12, 3, nullptr), CALCULATOR_INVALID_ARGUMENT);
}
