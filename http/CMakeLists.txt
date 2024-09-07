cmake_minimum_required(VERSION 3.10)
project(http)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(./ SRC)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/*.h)

add_library(http STATIC ${SRC} ${HEADERS})