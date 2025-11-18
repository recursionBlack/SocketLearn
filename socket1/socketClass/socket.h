#pragma once
#include <string>

#include <sys/socket.h>   // 核心 Socket 函数（socket、bind、connect 等）
#include <netinet/in.h>   // 网络地址结构（sockaddr_in 等）
#include <arpa/inet.h>    // 地址转换函数（inet_addr、inet_ntoa 等）
#include <unistd.h>       // 关闭 Socket 的 close() 函数
#include <fcntl.h>

namespace yazi
{
    namespace socket
    {
        class Socket
        {
            public:
                Socket();
                explicit Socket(int socketFd);
                ~Socket();

                bool bind(const std::string& ip, int port);
                bool listen(int backlog);
                bool connect(const std::string& ip, int port);
                int accept();
                // 返回实际发送数据的长度
                int send(const char* buf, int len);
                int recv(char* buf, int len);
                void close();

                bool set_non_blocking();
                bool set_send_buffer(int size);
                bool set_recv_buffer(int size);
                bool set_linger(bool active, int secondes);
                bool set_keepalive();
                bool set_reuseaddr();

            protected:
                std::string m_ip;   // ip
                int m_port;         // 端口
                int m_sockFd;       // 文件描述符

        };
    }

}