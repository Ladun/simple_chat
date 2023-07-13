#pragma once

#include <LDServerEngine.hpp>

namespace client
{
    class ServerSession: public net_core::Session
    {
    public:
        ServerSession(net_core::SocketType socket);
        ~ServerSession();

        void on_connected() override;
        void on_send(std::size_t sendSize) override;
        void on_disconnected() override;

    private:
        net_core::Buffer sendbuffer_;
    };
}