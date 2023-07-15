
#include <iostream>

#include "client_session.hpp"


namespace ld_server
{
    ClientSession::ClientSession(net_core::SocketType socket, Server* server)
        : Session(std::move(socket)), server_(server)
    {

    }

    ClientSession::~ClientSession()
    {

    }


    void ClientSession::on_connected()
    {
        std::cout << socket_.remote_endpoint().address().to_string() << " connected\n";
    }

    void ClientSession::on_send(std::size_t sendSize)
    {
        // std::cout << "Send size: " << sendSize << '\n';

    }
    void ClientSession::on_disconnected() 
    {
        std::cout << "disconnected\n";

        server_->close();

    }
}