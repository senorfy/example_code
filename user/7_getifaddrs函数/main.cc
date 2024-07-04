#include <iostream>
#include <stdlib.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    struct ifaddrs *ifaddr, *ifa;

    // 获取网络接口信息
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    // 遍历网络接口列表
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        cout << "ifa_name : " << ifa->ifa_name <<endl;

        if(ifa->ifa_addr) {
			cout << "ifa_addr : " << ifa->ifa_addr->sa_family << endl;
		}
    }

    // 释放资源
    freeifaddrs(ifaddr);
    return 0;
}