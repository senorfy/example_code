# 指定cmake版本
cmake_minimum_required(VERSION 3.5.1)

# 添加要编译的可执行文件
add_executable(fifo_read fifo_read_main.cpp)
add_executable(fifo_write fifo_write_main.cpp)

# 编译指令
# cmake -B build
# cd build 
# make
