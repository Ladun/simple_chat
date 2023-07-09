#pragma once

#include <LDServerEngine.hpp>

namespace server
{
    class CClientSession: public net_core::CSession
    {
    public:
        CClientSession(net_core::SocketType socket);
        ~CClientSession();

        void on_connected() override;
        void on_send(std::size_t sendSize) override;
        void on_disconnected() override;
    };
}