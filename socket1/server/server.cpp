#include <iostream>

#include <sys/socket.h>   // 核心 Socket 函数（socket、bind、connect 等）
#include <netinet/in.h>   // 网络地址结构（sockaddr_in 等）
#include <arpa/inet.h>    // 地址转换函数（inet_addr、inet_ntoa 等）
#include <unistd.h>       // 关闭 Socket 的 close() 函数

#include <string>
#include <cstring>

int main()
{
    // 1.创建socket,获得一个文件描述符file distrustion, 被成为“监听套接字”
    int socketFd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd < 0)
    {
        printf("create socket error: errno=%d errmsg=%s \n", errno, strerror(errno));
        return 1;
    }
    else{
        printf("create socket success! \n");
    }

    // 2. 绑定socket 到一个ip和端口port
    std::string ip = "127.0.0.1";
    int port = 8080;

    struct sockaddr_in sockaddr;
    // 清空内容，全部置换为0
    std::memset(&sockaddr, 0, sizeof(sockaddr));
    // 协议族
    sockaddr.sin_family = AF_INET;
    // ip地址
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    // 端口 本地字节序转为网络socket字节序，home to net socket
    sockaddr.sin_port = htons(port);
    if(::bind(socketFd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        printf("socket bind error: error=%d errmsg=%s \n" , errno, strerror(errno));
        return 1;
    }
    else{
        printf("socket bind success: ip=%s port=%d \n", ip.c_str(), port);
    }

    // 3.监听客户端的请求
    if(::listen(socketFd, 1024) < 0)
    {
        printf("socket listen error: errno=%d, errmsg=%s \n", errno, strerror(errno));
        return 1;
    }
    else{
        printf("socket listening ... \n");
    }
    
    // 4.接收客户端连接
    while(true)
    {
        // 连接成功时，创建一个新的文件描述符，被称为"连接套接字"
        int connFd = ::accept(socketFd, nullptr, nullptr);
        if (connFd < 0)
        {
            printf("socket accept error: errno=%d, errmsg=%s \n", errno, strerror(errno));
            return 1;
        }
        // 创建接收的缓存buffer
        char buf[1024] = {0};

        // 5.接收客户端的数据
        size_t len = ::recv(connFd, buf, sizeof(buf), 0);
        printf("recv: connfd=%d msg=%s \n", connFd, buf);

        // 6.服务端向客户端发送数据
        ::send(connFd, buf, len, 0);

    }

    // 7.关闭socket,参数为服务端的监听套接字
    ::close(socketFd);

    return 0;
}