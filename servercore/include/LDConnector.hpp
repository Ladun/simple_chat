#pragma once

#include <functional>
#include "LDSession.hpp"

namespace net_core
{
    class CConnector
    {

    public:
        CConnector(std::function<SessionPtr(SocketType)> session_factory,
                  const std::string& host, 
                  const std::string& port);
        ~CConnector();

        void start_connect();
    
    private:
        std::function<SessionPtr(SocketType)> session_factory_;

        ResolverType resolver_;
        ResolverType::iterator endpoint_iterator_;
    };
}