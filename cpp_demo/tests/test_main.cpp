#include "test_support.h"

#include <iostream>

namespace {

class SummaryListener final : public ::testing::EmptyTestEventListener {
public:
    void OnTestProgramEnd(const ::testing::UnitTest &unitTest) override
    {
        std::cout << "[listener] " << unitTest.successful_test_count() << " passed, "
                  << unitTest.failed_test_count() << " failed\n";
    }
};

}

bool DemoEnvironment::ready_ = false;

bool DemoEnvironment::isReady()
{
    return ready_;
}

void DemoEnvironment::SetUp()
{
    ready_ = true;
}

void DemoEnvironment::TearDown()
{
    ready_ = false;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new DemoEnvironment);
    ::testing::UnitTest::GetInstance()->listeners().Append(new SummaryListener);
    return RUN_ALL_TESTS();
}
