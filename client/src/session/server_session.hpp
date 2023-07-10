#pragma once

#include <LDServerEngine.hpp>

namespace client
{
    class CServerSession: public net_core::CSession
    {
    public:
        CServerSession(net_core::SocketType socket);
        ~CServerSession();

        void on_connected() override;
        void on_send(std::size_t sendSize) override;
        void on_disconnected() override;
    };
}