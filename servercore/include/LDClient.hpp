#pragma once

#include "LDCore.hpp"
#include "LDConnector.hpp"

namespace net_core
{
    class IClient
    {
    public:
        IClient();
        virtual ~IClient();

    public:
        virtual ErrCode init();
        virtual ErrCode close();
        ErrCode run();
    
    private:
        std::unique_ptr<CConnector> connector;
    };
}