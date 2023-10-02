project(SolverTests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCES Solver_tests.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    GTest::gtest 
    GTest::gtest_main
    Solver
)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

gtest_discover_tests(${PROJECT_NAME})
