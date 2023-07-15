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
        std::array<char, 30> nickname;
        std::array<char, 992> message;
    };
}