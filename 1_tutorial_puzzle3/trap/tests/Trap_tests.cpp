#include "Trap.h"
#include <gtest/gtest.h>

struct TestInOut{
    TestInOut(const char* trap_log, const int id, const TrapStatus status) : 
        m_TrapLog(trap_log), 
        m_Id(id),
        m_Status(status){}
    const std::string m_TrapLog;
    int m_Id;
    TrapStatus m_Status;
};
class ParseIdTests : public ::testing::TestWithParam<TestInOut> {
};

TEST_P(ParseIdTests, parsing)
{
    Trap trap;
    trap.Init(GetParam().m_TrapLog);
    EXPECT_EQ(trap.id_, GetParam().m_Id);
    EXPECT_EQ(trap.status_, GetParam().m_Status);
}

TestInOut inOuts [] = {
    TestInOut("   1: idle reversed ready reversed toggled reversed reversed",       1   , TrapStatus::kActivated), 
    TestInOut("   + 0123: idle reversed ready reversed toggled reversed",  123 , TrapStatus::kDeactivated), 
    TestInOut("   0: idle reversed ready ",       0   , TrapStatus::kActivated), 
};
INSTANTIATE_TEST_CASE_P(
        ParsingTestSuite,
        ParseIdTests,
        ::testing::ValuesIn(inOuts)
        );
