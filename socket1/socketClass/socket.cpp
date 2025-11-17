#include "socket.h"

#include <cstring>

using namespace yazi::socket;


Socket::Socket() : m_ip(""), m_port(0), m_sockFd(0)
{
    // 1.创建socket,获得一个文件描述符file distrustion, 被成为“监听套接字”
    m_sockFd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockFd < 0)
    {
        printf("create socket error: errno=%d errmsg=%s \n", errno, strerror(errno));
    }
}

Socket::Socket(int socketFd): m_ip(""), m_port(0), m_sockFd(socketFd)
{

}

Socket::~Socket()
{
    close();
}

bool Socket::bind(const std::string &ip, int port)
{
    // 2. 绑定socket 到一个ip和端口port
    struct sockaddr_in sockaddr;
    // 清空内容，全部置换为0
    std::memset(&sockaddr, 0, sizeof(sockaddr));
    // 协议族
    sockaddr.sin_family = AF_INET;
    if (ip.empty())
    {
        // ip为空，绑定任意本地网卡ip
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else{
        // ip地址
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    }

    // 端口 本地字节序转为网络socket字节序，home to net socket
    sockaddr.sin_port = htons(port);
    if(::bind(m_sockFd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        printf("socket bind error: error=%d errmsg=%s \n" , errno, strerror(errno));
        return false;
    }
    m_ip = ip;
    m_port = port;
    printf("socket bind success: ip=%s port=%d \n", ip.c_str(), port);

    return true;
}

bool Socket::listen(int backlog)
{
    // 3.监听客户端的请求
    if(::listen(m_sockFd, backlog) < 0)
    {
        printf("socket listen error: errno=%d, errmsg=%s \n", errno, strerror(errno));
        return false;
    }
    printf("socket listening ... \n");

    return true;
}

bool Socket::connect(const std::string &ip, int port)
{
    // 2.连接服务端
    struct sockaddr_in sockaddr1;
    // 清空内容，全部置换为0
    std::memset(&sockaddr1, 0, sizeof(sockaddr1));
    // 协议族
    sockaddr1.sin_family = AF_INET;
    // ip地址
    sockaddr1.sin_addr.s_addr = inet_addr(ip.c_str());
    // 端口 本地字节序转为网络socket字节序，home to net socket
    sockaddr1.sin_port = htons(port);
    if(::connect(m_sockFd, (struct sockaddr *)&sockaddr1, sizeof(sockaddr1)) < 0)
    {
        printf("socket connect error: errno=%d, errmsg=%s \n", errno, strerror(errno));
        return false;
    }

    m_ip = ip;
    m_port = port;

    return true;
}

int Socket::accept()
{
    // 连接成功时，创建一个新的文件描述符，被称为"连接套接字"
    int connFd = ::accept(m_sockFd, nullptr, nullptr);
    if (connFd < 0)
    {
        printf("socket accept error: errno=%d, errmsg=%s \n", errno, strerror(errno));
        return false;
    }

    printf("recv: connfd=%d\n", connFd);

    return connFd;
}

int Socket::send(const char *buf, int len)
{
    // 3. 向服务端，发送数据
    return ::send(m_sockFd, buf, len, 0);
}

int Socket::recv(char *buf, int len)
{
    return ::recv(m_sockFd, buf, sizeof(buf), 0);
}

void Socket::close()
{
    if (m_sockFd > 0)
    {
        ::close(m_sockFd);
        m_sockFd = 0;
    }
}
