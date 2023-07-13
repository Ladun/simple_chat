#pragma once

#include <LDServerEngine.hpp>

namespace server
{
    class ClientSession: public net_core::Session
    {
    public:
        ClientSession(net_core::SocketType socket);
        ~ClientSession();

        void on_connected() override;
        void on_send(std::size_t sendSize) override;
        void on_disconnected() override;
    };
}