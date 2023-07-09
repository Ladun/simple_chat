#pragma once

#include <functional>
#include "LDSession.hpp"


namespace net_core
{
    class CListner
    {
    public:
        CListner(std::function<SessionPtr(SocketType)> session_factory,
                 const EndpointType& endpoint);
        ~CListner();
        
        void start_accept();


    private:
        std::function<SessionPtr(SocketType)> session_factory_;
        AcceptorType acceptor_;

    };
}