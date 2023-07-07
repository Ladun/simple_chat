#pragma once

#include <map>
#include <functional>

#include "LDCore.hpp"
#include "LDPacketHeader.hpp"


namespace net_core
{
    class CMessageHandler
    {
    public:
        using HandlerType = std::function<ErrCode(CPacketHeader*, Size)>;

    public:
        CMessageHandler() = default;
        ~CMessageHandler() = default;
        ErrCode register_handler(MessageNo pNumber, HandlerType&& pHandler);
        template<typename... TArgs>
        ErrCode process(MessageNo pNumber, TArgs... pArgs);

		static CMessageHandler&	instance() { return singleton_; }
        
    private:
        static CMessageHandler singleton_;

        std::map<MessageNo, HandlerType> handler_list_;
    };
}