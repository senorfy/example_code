#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

using namespace std;

#define SOCKET_PATH "/tmp/socket_path"

int main() {
    // 创建套接字
    int serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cout << "Failed to create socket." << endl;
        return 1;
    }

    // 绑定地址
    struct sockaddr_un serverAddress;
    serverAddress.sun_family = AF_UNIX;
    strncpy(serverAddress.sun_path, SOCKET_PATH, sizeof(serverAddress.sun_path) - 1);
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cout << "Failed to bind socket." << endl;
        close(serverSocket);
        return 1;
    }

    // 监听连接
    if (listen(serverSocket, 1) == -1) {
        cout << "Failed to listen for connections." << endl;
        close(serverSocket);
        return 1;
    }

    cout << "服务器启动，等待客户端连接..." << endl;

    // 接受客户端连接
    struct sockaddr_un clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        cout << "Failed to accept client connection." << endl;
        close(serverSocket);
        return 1;
    }

    cout << "客户端已连接." << endl;

    while (true) {
        // 接收客户端数据
        char buffer[1024];
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            cout << "Failed to read from client." << endl;
            close(clientSocket);
            close(serverSocket);
            return 1;
        } else if (bytesRead == 0) {
            // 客户端已关闭连接
            break;
        }

        cout << "接收到客户端数据: " << buffer << endl;

        // 发送响应数据给客户端
        string response = "已收到消息: " + string(buffer);
        ssize_t bytesWritten = write(clientSocket, response.c_str(), response.length());
        if (bytesWritten == -1) {
            cout << "Failed to write to client." << endl;
            close(clientSocket);
            close(serverSocket);
            return 1;
        }
    }

    // 关闭连接
    close(clientSocket);
    close(serverSocket);

    return 0;
}