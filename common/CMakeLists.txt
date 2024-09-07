cmake_minimum_required(VERSION 3.10)
project(common)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(./ SRC)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/*.h)

add_library(common STATIC ${SRC} ${HEADERS})