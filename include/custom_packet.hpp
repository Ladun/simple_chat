#pragma once

#include <LDServerEngine.hpp>

namespace net_packet
{
    enum class PacketCode: net_core::MessageNo
    {
        CHAT
    };

    class ChatPacket : public net_core::PacketHeader
    {
    public:
        ChatPacket() = default;
        ~ChatPacket() = default;

    public:
        int data;
    };
}