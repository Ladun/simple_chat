#pragma once 

#include "LDCore.hpp"

namespace net_core
{
    using MessageNo = unsigned short;

    #pragma pack(push, 1)
    class PacketHeader
    {
    public:
        MessageNo message_{};        
    };
    #pragma pack(pop)

    // Packet header size
    constexpr Size ePacketHeaderSize = sizeof(PacketHeader);
}