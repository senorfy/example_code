# 指定cmake版本
cmake_minimum_required(VERSION 3.5.1)

# 添加要编译的可执行文件
add_executable(read read_main.cpp)
add_executable(write write_main.cpp)

# 编译指令
# cmake -B build
# cd build 
# make
