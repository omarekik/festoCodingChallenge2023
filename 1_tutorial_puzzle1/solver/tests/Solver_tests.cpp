#include "Solver.h"

#include <gtest/gtest.h>
#include <string>

TEST(SolverTests, sorted)
{
    std::string input = "abc";
    ASSERT_TRUE(is_ordered(input));
}

TEST(SolverTests, unsorted)
{
    std::string input = "acb";
    EXPECT_FALSE(is_ordered(input));
    input = "cbd";
    EXPECT_FALSE(is_ordered(input));
    input = "cb";
    EXPECT_FALSE(is_ordered(input));
}