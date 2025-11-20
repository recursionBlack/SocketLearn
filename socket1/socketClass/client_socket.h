#pragma once

#include "socket.h"
#include <string>

namespace yazi
{
    namespace socket
    {
        class ClientSocket : public Socket
        {
            public:
                ClientSocket() = delete;
                ClientSocket(const std::string ip, int port);
                ~ClientSocket() = default;
        };
    }
}