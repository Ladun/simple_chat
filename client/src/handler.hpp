#pragma once

#include <LDServerEngine.hpp>
#include "session/server_session.hpp"
#include "custom_packet.hpp"

namespace client
{

    net_core::ErrCode ChatPacketHandler(net_core::PacketHeader* header, net_core::Size size, net_core::Session* session)
    {
        auto packet = reinterpret_cast<net_packet::ChatPacket*>(header);
        auto ssession = reinterpret_cast<ServerSession*>(session);

        std::cout << "[Receive] data: " << packet->data<<"\n";

        return 0;
    }
}