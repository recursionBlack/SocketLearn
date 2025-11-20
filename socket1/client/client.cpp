#include <iostream>

#include "socketClass/client_socket.h"
using namespace yazi::socket;

int main()
{
    // 1.创建客户端socket
    ClientSocket client("127.0.0.1", 8080);

    // 3. 向服务端，发送数据
    std::string data = "hello world";
    int ds = data.size();
    int ds2 = client.send(data.c_str(), data.size());

    // 4.客户端接收服务端的数据
    char buf[1024] = {0};
    client.recv(buf, sizeof(buf));
    printf("recv: %s \n", buf);

    return 0;
}