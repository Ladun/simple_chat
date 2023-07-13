
#include <iostream>

#include "client_session.hpp"


namespace server
{
    ClientSession::ClientSession(net_core::SocketType socket)
        : Session(std::move(socket))
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
        std::cout << "Send size: " << sendSize << '\n';

    }
    void ClientSession::on_disconnected() 
    {
        std::cout << "disconnected\n";

    }
}