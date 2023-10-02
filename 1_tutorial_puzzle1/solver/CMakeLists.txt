project(Solver)

add_subdirectory(tests)

set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/Solver.h
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/Solver.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} )

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
