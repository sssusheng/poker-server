cmake_minimum_required(VERSION 3.22)
project(tcp)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件和头文件
aux_source_directory(./ SRC)

# 创建静态库
add_library(tcp STATIC ${SRC}
        TcpConnection.h
        TcpServer.h
)

