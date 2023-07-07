#pragma once

#include "LDCore.hpp"
#include "LDListner.hpp"

namespace net_core
{
    class IServer
    {
    public:
        IServer();
        virtual ~IServer();

    public:
        virtual ErrCode init();
        virtual ErrCode close();
        ErrCode run();
    
    private:
        std::unique_ptr<CListner> listner;
    };
}