cmake_minimum_required(VERSION 3.22)
project(poker_server)

set(CMAKE_CXX_STANDARD 17)

# 添加头文件路径
include_directories(
        ${PROJECT_SOURCE_DIR}/common
        ${PROJECT_SOURCE_DIR}/reactor
        ${PROJECT_SOURCE_DIR}/thread
)

# 添加子目录
add_subdirectory(common)
add_subdirectory(reactor)
add_subdirectory(thread)

link_libraries(thread reactor common)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(poker_server main.cpp)
