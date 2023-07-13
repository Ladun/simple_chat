#pragma once

#include "LDCore.hpp"
#include "LDSession.hpp"
#include <cstring>

namespace net_core
{
    class Connector
    {
    public:
        Connector(std::function<SessionPtr(SocketType)> session_factory,
                  const std::string& host, 
                  const std::string& port);
        ~Connector();

        ErrCode connect();

        Session* get_session() const{
            return session_.get();
        }
    
    private:
        std::function<SessionPtr(SocketType)> session_factory_;

        SessionPtr session_;

        std::string host_;
        std::string port_;
        ResolverType resolver_;
    };
}