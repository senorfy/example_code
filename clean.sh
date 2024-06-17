#!/bin/bash

clear_build_folders() {
    local root_dir=$1

    # 遍历目录下的所有文件和文件夹
    for item in "$root_dir"/*; do
        if [ -d "$item" ]; then
            # 判断是否为"build"文件夹
            if [ "$(basename "$item")" = "build" ]; then
                echo "Removing folder: $item"
                rm -rf "$item"
            else
                # 递归调用清除函数
                clear_build_folders "$item"
            fi
        fi
    done
}

# 指定要清除的目录路径
directory_path=$(pwd)

# 调用函数清除目录下的"build"文件夹
clear_build_folders "$directory_path"
