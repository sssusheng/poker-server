cmake_minimum_required(VERSION 3.22)
project(poker_server)

set(CMAKE_CXX_STANDARD 17)

# 添加子目录
add_subdirectory(common)


add_executable(poker_server main.cpp)
