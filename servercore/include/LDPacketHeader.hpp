#pragma once 

namespace net_core
{
    using MessageNo = unsigned long;

    #pragma pack(push, 1)
    class CPacketHeader
    {
    public:
        MessageNo message_{};
    };
    #pragma pack(pop)
}