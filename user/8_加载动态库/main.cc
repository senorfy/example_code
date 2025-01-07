#include <iostream>
#include <dlfcn.h>

//调用时传入绝对路径或相对路径，则尝试从指定的路径加载共享库。
//传递的文件名只是库的名称而没有路径信息，。这些默认路径通常包括 /lib、/usr/lib、/lib64、/usr/lib64 等。
#define LIB_NAME "./libcdnprint.so"

typedef void (*hello)();

int main() {
    void *handle;
    hello abc;
    handle = dlopen(LIB_NAME, RTLD_NOW);
    if (!handle) {
        std::cout << "cdn" << std::endl;
        return 1;
    }

    void *sym = dlsym(handle, "cdn_printf_hello_world");
    abc = (hello)sym;
    if (!abc) {
        dlclose(handle);
        std::cout << "cdn1" << std::endl;
        return 1;
    }

    abc(); // 调用共享库中的函数

    void *sym1 = dlsym(handle, "abc");
    int* num = (int*)sym1;
    if (!num) {
        dlclose(handle);
        std::cout << "cdn2" << std::endl;
        return 1;
    }

    std::cout << *num << std::endl;

    return 0;
}