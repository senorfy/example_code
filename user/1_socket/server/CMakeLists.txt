# 指定cmake版本
cmake_minimum_required(VERSION 3.5.1)

# 指定项目的名称，一般和项目的文件夹名称对应
project(socket_server_local)

# 源文件目录
aux_source_directory(. DIR_SRCS)

# 设置环境变量，编译用到的源文件全部都要放到这
set(TEST_MATH ${DIR_SRCS})

# 库文件目录
#link_directories(lib)

# 添加要编译的可执行文件
add_executable(${PROJECT_NAME} ${TEST_MATH})
target_link_libraries(${PROJECT_NAME})
