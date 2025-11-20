#include <iostream>

#include "socketClass/server_socket.h"
using namespace yazi::socket;

int main()
{
    // 1.创建socket,获得一个文件描述符file distrustion, 被成为“监听套接字”
    ServeSocket server("127.0.0.1", 8080);
    
    // 4.接收客户端连接
    while(true)
    {
        // 连接成功时，创建一个新的文件描述符，被称为"连接套接字"
        int connFd = server.accept();
        if (connFd < 0)
        {
            return 1;
        }
        Socket client(connFd);

        // 创建接收的缓存buffer
        char buf[1024] = {0};

        // 5.接收客户端的数据
        size_t len = client.recv(buf, sizeof(buf));
        printf("recv: connfd=%d msg=%s \n", connFd, buf);

        // 6.服务端向客户端发送数据
        client.send(buf, len);

    }

    return 0;
}