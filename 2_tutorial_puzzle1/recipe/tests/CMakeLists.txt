project(RecipeCheckerTests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCES RecipeCheckerTests.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    GTest::gtest 
    GTest::gtest_main
    RecipeChecker
)

gtest_discover_tests(${PROJECT_NAME})
