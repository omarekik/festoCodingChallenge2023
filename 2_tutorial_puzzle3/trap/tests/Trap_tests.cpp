#include "Trap.h"
#include <gtest/gtest.h>

struct TestInOut{
    TestInOut(const char* trap_log, const Scale scale, const bool is_safe) : 
        trap_log(trap_log), 
        scale(scale),
        is_safe(is_safe)
        {}
    const std::string trap_log;
    Scale scale;
    bool is_safe;
};
class ParseIdTests : public ::testing::TestWithParam<TestInOut> {
};

TEST_P(ParseIdTests, parsing)
{
    Trap trap;
    trap.Init(GetParam().trap_log);
    EXPECT_EQ(trap.scale_, GetParam().scale);
    EXPECT_EQ(trap.Check(), GetParam().is_safe);
}

TestInOut inOuts [] = {
    TestInOut("33: 29 59 90 - 16 23244 2386229038", {33, {29, 59, 90}, {16, 23244, 2386229038}}, false), // parsing
    TestInOut("   4: 42 87 - 29 1219  ", {4, {42, 87}, {29, 1219}}, false), // parsing
    TestInOut("1029: 9 - 16 622", {1029, {9}, {16, 622}}, false), // parsing
    TestInOut("1030: 20 - 20", {1030, {20}, {20}}, false), // check diversity
    TestInOut("1031: 2 - 3 6", {1031, {2}, {3, 6}}, false), // check count equility
    TestInOut("1032: 4 10 - 5 10", {1032, {4, 10}, {5, 10}}, false), // check value equility
    TestInOut("1033: 4 20 - 5 10", {1033, {4, 20}, {5, 10}}, true), // check success 
    TestInOut("1034: 2 9999999999999999999 - 3 6", {1034, {2, 9999999999999999999}, {3, 6}}, false) // check precision 
};
INSTANTIATE_TEST_CASE_P(
        ParsingTestSuite,
        ParseIdTests,
        ::testing::ValuesIn(inOuts)
        );
