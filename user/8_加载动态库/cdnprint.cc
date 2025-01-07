#include <iostream>
#include <net/if.h>
#include <cstring>


#ifdef __cplusplus
extern "C"{
#endif

void cdn_printf_hello_world();


#ifdef __cplusplus
}
#endif

int abc = 10;

void cdn_printf_hello_world()
{
    std::cout << "cdn printf hello world" << std::endl;
}