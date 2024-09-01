cmake_minimum_required(VERSION 3.22)
project(thread)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件和头文件
aux_source_directory(./ SRC)

# 创建静态库
add_library(thread STATIC ${SRC}
        WorkerThread.h
        ThreadPool.h
)

