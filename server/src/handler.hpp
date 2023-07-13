#pragma once

#include <LDServerEngine.hpp>
#include "session/client_session.hpp"
#include <custom_packet.hpp>

#include <iostream>

namespace server
{

    net_core::ErrCode ChatPacketHandler(net_core::PacketHeader* header, net_core::Size size, net_core::Session* session)
    {
        auto packet = reinterpret_cast<net_packet::ChatPacket*>(header);

        std::cout << "[Receive] data: " << packet->data<<"\n";

        net_packet::ChatPacket sPacket{};
        sPacket.data = 2;
        
        session->send<net_packet::ChatPacket>(sPacket);  
        return 0;
    }
}