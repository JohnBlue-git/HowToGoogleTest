#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "test_support.h"

class FixtureLifecycleTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        resource_ = std::make_unique<std::string>("ready");
    }

    void TearDown() override
    {
        EXPECT_NE(resource_, nullptr);
        resource_.reset();
    }

    std::unique_ptr<std::string> resource_;
};

TEST_F(FixtureLifecycleTest, SetUpPreparesTestResource)
{
    ASSERT_NE(resource_, nullptr);
    EXPECT_EQ(*resource_, "ready");
}

TEST(GlobalEnvironmentTest, EnvironmentIsInitializedForEveryTest)
{
    EXPECT_TRUE(DemoEnvironment::isReady());
}
