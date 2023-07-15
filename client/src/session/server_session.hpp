#pragma once

#include <LDServerEngine.hpp>
#include "../client.hpp"

namespace ld_client
{
    class ServerSession: public net_core::Session
    {
    public:
        ServerSession(net_core::SocketType socket, Client* client);
        ~ServerSession();

        void on_connected() override;
        void on_send(std::size_t sendSize) override;
        void on_disconnected() override;

    private:
        Client* client_;
    };
}