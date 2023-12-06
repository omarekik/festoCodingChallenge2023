project(Start)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Trap
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${Trap_SOURCE_DIR}/include
)
