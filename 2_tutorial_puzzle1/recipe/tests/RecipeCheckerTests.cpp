#include "RecipeChecker.h"
#include <gtest/gtest.h>

struct TestInOut{
    TestInOut(const char* recipe_log, const std::vector<std::pair<int, int>> recipe, const char* key) : 
        recipe_log_(recipe_log), 
        recipe_(recipe),
        key_(key){}
    const std::string recipe_log_;
    const std::vector<std::pair<int, int>> recipe_;
    const std::string key_;
};
class ParseRecipeTests : public ::testing::TestWithParam<TestInOut> {
};

TEST_P(ParseRecipeTests, parsing)
{
    RecipeChecker recipe_checker;
    recipe_checker.Init(GetParam().recipe_log_);
    EXPECT_EQ(recipe_checker.recipe_, GetParam().recipe_);
    auto key = recipe_checker.Check();
    EXPECT_STREQ(key.value_or("").c_str(), GetParam().key_.c_str());
}

TestInOut inOuts [] = {
    TestInOut("(1, 1) - (6, 2) - (3, 1) - (1, 1)", {{1, 1}, {6, 2}, {3, 1}, {1, 1}}, ""), 
    TestInOut("(2, 1) - (3, 3) - (5, 1) - ",  {{2, 1}, {3, 3}, {5, 1}}, ""), 
    TestInOut(" (3, 2) ", {{3, 2}}, ""),
    TestInOut("(1, 1) - (3, 1) - (7, 2)", {{1, 1}, {3, 1}, {7, 2}}, "DAFC"),
    TestInOut("(1, 1) - (6, 2) - (4, 1) - (7, 2) - (3, 1) - (7, 2) - (1, 2) - (6, 3) - (8, 1) - (3, 3) - (7, 3) - (2, 2) - (9, 4)", {{1, 1} , {6, 2} , {4, 1} , {7, 2} , {3, 1} , {7, 2} , {1, 2} , {6, 3} , {8, 1} , {3, 3} , {7, 3} , {2, 2} , {9, 4}}, "")
};
INSTANTIATE_TEST_CASE_P(
        ParsingTestSuite,
        ParseRecipeTests,
        ::testing::ValuesIn(inOuts)
        );
