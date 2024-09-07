cmake_minimum_required(VERSION 3.10)
project(tcp)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件和头文件
aux_source_directory(./ SRC)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/*.h)

add_library(tcp STATIC ${SRC} ${HEADERS})

