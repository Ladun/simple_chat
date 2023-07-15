
#include <iostream>

#include "server_session.hpp"

namespace ld_client
{
    ServerSession::ServerSession(net_core::SocketType socket, Client* client)
        : Session(std::move(socket)), client_(client)
    {

    }

    ServerSession::~ServerSession()
    {

    }

    void ServerSession::on_connected()
    {
        std::cout << "Connect to " << socket_.remote_endpoint().address().to_string() << " \n";

    }
    void ServerSession::on_send(std::size_t sendSize)
    {
        // std::cout << "Send size: " << sendSize << '\n';
    }
    
    void ServerSession::on_disconnected() 
    {
        std::cout << "disconnected\n";

        client_->close();
    }
}