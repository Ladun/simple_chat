#pragma once

#include <map>
#include <functional>

#include "LDCore.hpp"
#include "LDPacketHeader.hpp"


namespace net_core
{
    class MessageHandler : public Singleton<MessageHandler>
    {
    public:
        using HandlerType = std::function<ErrCode(PacketHeader*, Size, Session*)>;

    public:
        MessageHandler() = default;
        ~MessageHandler() = default;
        ErrCode register_handler(MessageNo pNumber, HandlerType&& pHandler)
        {
            auto aResult = handler_list_.emplace(pNumber, pHandler);
            if (aResult.second == false)
                return eErrCodeAlreadyRegistered;

            return 0;
        }
	
        template<typename... TArgs>
        ErrCode process(MessageNo pNumber, TArgs... pArgs)
        {
            auto aIter = handler_list_.find(pNumber);
            if (aIter == handler_list_.end())
                return eErrCodeInvalidMessage;

            auto aResult = aIter->second(pArgs...);
            return aResult;
        }
        
    private:

        std::map<MessageNo, HandlerType> handler_list_;
    };
}