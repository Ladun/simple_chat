#pragma once

#include <functional>
#include "LDSession.hpp"

namespace net_core
{
    class CConnector
    {
    public:
        using __SessionPtr = std::shared_ptr<CSession>;
        using SocketType = boost::asio::ip::tcp::socket;
        using ResolverType = boost::asio::ip::tcp::resolver;

    public:
        CConnector(std::function<__SessionPtr(SocketType)> session_factory,
                  const std::string& host, 
                  const std::string& port);
        ~CConnector();

        void start_connect();
    
    private:
        std::function<__SessionPtr(SocketType)> session_factory_;

        ResolverType resolver_;
        ResolverType::iterator endpoint_iterator_;
    };
}