cmake_minimum_required(VERSION 3.17)
project(Start)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPROJECT_PATH=\"${PROJECT_SOURCE_DIR}\")

include(GoogleTest)
enable_testing ()

add_subdirectory(solver)
add_subdirectory(main)

install(TARGETS Start DESTINATION bin)
