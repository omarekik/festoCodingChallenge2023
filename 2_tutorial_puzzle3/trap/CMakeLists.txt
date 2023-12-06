project(Trap)

add_subdirectory(tests)

find_package(Boost COMPONENTS boost log REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/Trap.h
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/Trap.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::log)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
