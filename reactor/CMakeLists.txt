cmake_minimum_required(VERSION 3.22)
project(reactor)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件和头文件
aux_source_directory(./ SRC)

# 创建静态库
add_library(reactor STATIC ${SRC}
        Dispatcher.h
        EpollDispatcher.h
        PollDispatcher.h
        SelectDispatcher.h
        EventLoop.h
)

