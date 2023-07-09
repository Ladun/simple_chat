
#include "client_session.hpp"

namespace server
{
    CClientSession::CClientSession(net_core::SocketType socket)
        : CSession(std::move(socket))
    {

    }

    CClientSession::~CClientSession()
    {

    }


    void CClientSession::on_connected()
    {

    }
    void CClientSession::on_send(std::size_t sendSize)
    {

    }
    void CClientSession::on_disconnected() 
    {

    }
}