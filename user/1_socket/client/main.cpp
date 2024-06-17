#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

using namespace std;

#define SOCKET_PATH "/tmp/socket_path"

int main() {
    // 创建套接字
    int clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cout << "Failed to create socket." << endl;
        return 1;
    }

    // 连接服务器
    struct sockaddr_un serverAddress;
    serverAddress.sun_family = AF_UNIX;
    strncpy(serverAddress.sun_path, SOCKET_PATH, sizeof(serverAddress.sun_path) - 1);
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cout << "Failed to connect to server." << endl;
        close(clientSocket);
        return 1;
    }

    cout << "已连接到服务器." << endl;

    while (true) {
        // 发送数据给服务器
        string message;
        cout << "请输入要发送的消息（输入 q 退出）: ";
        getline(cin, message);

        if (message == "q") {
            break;
        }

        ssize_t bytesWritten = write(clientSocket, message.c_str(), message.length());
        if (bytesWritten == -1) {
            cout << "Failed to write to server." << endl;
            close(clientSocket);
            return 1;
        }

        // 接收服务器响应
        char buffer[1024];
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            cout << "Failed to read from server." <<endl;
            close(clientSocket);
            return 1;
        }

        cout << "收到服务器响应: " << buffer << endl;
    }

    // 关闭连接
    close(clientSocket);

    return 0;
}