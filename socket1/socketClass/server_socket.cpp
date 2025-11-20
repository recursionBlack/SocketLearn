#include "server_socket.h"

using namespace yazi::socket;

ServeSocket::ServeSocket(const std::string &ip, int port) : Socket()
{
    // 监听套接字启动的流程
    // set_non_blocking();
    set_recv_buffer(10 * 1024);
    set_send_buffer(10 * 1024);
    set_linger(true, 0);
    set_keepalive();
    set_reuseaddr();
    bind(ip, port);     // 必须要有的
    listen(1024);   // 必须要有的

}

