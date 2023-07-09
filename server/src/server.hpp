#pragma once

#include <LDServerEngine.hpp>


namespace server
{
    class CServer
    {
    public:
        CServer(int port);
        ~CServer();

        void run();

    private:
        net_core::CListner listner_;
    };
}