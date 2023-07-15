#pragma once

#include <LDServerEngine.hpp>

#include "../server.hpp"

namespace ld_server
{
    class ClientSession: public net_core::Session
    {
    public:
        ClientSession(net_core::SocketType socket, Server* server);
        ~ClientSession();

        void on_connected() override;
        void on_send(std::size_t sendSize) override;
        void on_disconnected() override;


    private:
        Server* server_;
    };
}