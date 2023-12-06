project(Start)

find_package(Boost COMPONENTS boost log REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Trap Boost::log
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${Trap_SOURCE_DIR}/include
)
