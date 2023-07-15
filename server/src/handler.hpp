#pragma once

#include <iostream>

#include <LDServerEngine.hpp>
#include <custom_packet.hpp>

#include "session/client_session.hpp"
#include "server.hpp"



namespace ld_server
{

    net_core::ErrCode ChatPacketHandler(net_core::PacketHeader* header, net_core::Size pSize, net_core::Session* session, Server* server)
    {   
        auto packet = reinterpret_cast<net_packet::ChatPacket*>(header);

        // std::cout << "Packet ptr: " << packet << ", ";
        // std::cout << "Receive size: " << pSize << ", ";
        // std::cout << "Session ptr: " << session << ", ";
        // std::cout << "Server ptr: " << server << "\n";

        std::cout << "Receive [" << packet->nickname.data() <<"]:";
        std::cout << packet->message.data() <<"\n"; 

        server->broadcast(*packet, sizeof(*packet));
        return 0;
    }
}