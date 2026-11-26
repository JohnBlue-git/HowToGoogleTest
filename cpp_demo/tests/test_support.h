#ifndef HOW_TO_GOOGLE_TEST_TEST_SUPPORT_H
#define HOW_TO_GOOGLE_TEST_TEST_SUPPORT_H

#include <gtest/gtest.h>

class DemoEnvironment final : public ::testing::Environment {
public:
    static bool isReady();

    void SetUp() override;
    void TearDown() override;

private:
    static bool ready_;
};

#endif
