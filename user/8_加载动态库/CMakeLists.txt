# 指定cmake版本
cmake_minimum_required(VERSION 3.5.1)

add_library(cdnprint SHARED cdnprint.cc)
add_executable(main main.cc)
target_link_libraries(main dl)

# 编译指令
# cmake -B build
# cd build 
# make
