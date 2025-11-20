#pragma once

#include "socket.h"
#include <string>
namespace yazi
{
    namespace socket
    {
        class ServeSocket : public Socket
        {
            public:
                ServeSocket() = delete;
                ServeSocket(const std::string& ip, int port);
                ~ServeSocket() = default;
        };
    }
}