
#include "server_session.hpp"

namespace client
{
    CServerSession::CServerSession(net_core::SocketType socket)
        : CSession(std::move(socket))
    {

    }

    CServerSession::~CServerSession()
    {

    }


    void CServerSession::on_connected()
    {

    }
    void CServerSession::on_send(std::size_t sendSize)
    {

    }
    void CServerSession::on_disconnected() 
    {

    }
}