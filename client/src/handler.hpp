#pragma once

#include <LDServerEngine.hpp>
#include "session/server_session.hpp"
#include "custom_packet.hpp"

namespace ld_client
{

    net_core::ErrCode ChatPacketHandler(net_core::PacketHeader* header, net_core::Size size, net_core::Session* session)
    {
        auto packet = reinterpret_cast<net_packet::ChatPacket*>(header);
        // auto ssession = reinterpret_cast<ServerSession*>(session);

        std::cout << "[" << packet->nickname.data() <<"]:";
        std::cout << packet->message.data() <<"\n";

        return 0;
    }
}