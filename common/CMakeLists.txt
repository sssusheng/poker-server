cmake_minimum_required(VERSION 3.22)
project(common)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(./ SRC)

add_library(common STATIC ${SRC}
        Channel.h
        Buffer.h
        Log.h
)