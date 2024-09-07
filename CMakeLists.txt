cmake_minimum_required(VERSION 3.10)
project(poker_server)

set(CMAKE_CXX_STANDARD 17)

# 添加头文件路径
include_directories(
        ${PROJECT_SOURCE_DIR}/common
        ${PROJECT_SOURCE_DIR}/reactor
        ${PROJECT_SOURCE_DIR}/thread
        ${PROJECT_SOURCE_DIR}/tcp
        ${PROJECT_SOURCE_DIR}/http
        ${PROJECT_SOURCE_DIR}/serialize
)

# 添加子目录
add_subdirectory(common)
add_subdirectory(reactor)
add_subdirectory(thread)
add_subdirectory(tcp)
add_subdirectory(http)
add_subdirectory(serialize)

link_libraries(tcp http thread reactor common serialize)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(poker_server main.cpp)
