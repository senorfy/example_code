#include <iostream>
#include <net/if.h>
#include <cstring>

using namespace std;

int main(void)
{
    struct if_nameindex *ifp = if_nameindex();/*函数定义在 <net/if.h> 头文件中， 用于获取系统上可用网络接口的列表*/

    if (!ifp) {
        cout << "occur error!!!" << endl;
        return -1;
    }
    
    struct if_nameindex *ifp_save = ifp;

    while (ifp->if_index) {
        cout << "if_index : " << ifp->if_index << " ,  if_name : " << ifp->if_name << endl;
        ifp++;
    }
    
    if_freenameindex(ifp_save);
    
    return    0;
}