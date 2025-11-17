#include <iostream>

#include <sys/socket.h>   // 核心 Socket 函数（socket、bind、connect 等）
#include <netinet/in.h>   // 网络地址结构（sockaddr_in 等）
#include <arpa/inet.h>    // 地址转换函数（inet_addr、inet_ntoa 等）
#include <unistd.h>       // 关闭 Socket 的 close() 函数

#include <string>
#include <cstring>

int main()
{
    // 1.创建客户端socket
    int socketFd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd < 0)
    {
        printf("create socket error: errno=%d errmsg=%s \n", errno, strerror(errno));
        return 1;
    }
    else{
        printf("create socket success! \n");
    }

    // 2.连接服务端
    std::string ip = "127.0.0.1";
    int port = 8080;

    struct sockaddr_in sockaddr1;
    // 清空内容，全部置换为0
    std::memset(&sockaddr1, 0, sizeof(sockaddr1));
    // 协议族
    sockaddr1.sin_family = AF_INET;
    // ip地址
    sockaddr1.sin_addr.s_addr = inet_addr(ip.c_str());
    // 端口 本地字节序转为网络socket字节序，home to net socket
    sockaddr1.sin_port = htons(port);
    if(::connect(socketFd, (struct sockaddr *)&sockaddr1, sizeof(sockaddr1)) < 0)
    {
        printf("socket connect error: errno=%d, errmsg=%s \n", errno, strerror(errno));
        return 1;
    }

    // 3. 向服务端，发送数据
    std::string data = "hello world";
    ::send(socketFd, data.c_str(), data.size(), 0);

    // 4.客户端接收服务端的数据
    char buf[1024] = {0};
    ::recv(socketFd, buf, sizeof(buf), 0);
    printf("recv: %s \n", buf);

    // 5.关闭socket
    ::close(socketFd);

    return 0;
}