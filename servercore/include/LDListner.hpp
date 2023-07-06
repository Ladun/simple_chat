#pragma once

#include <functional>
#include "LDSession.hpp"


namespace net_core
{
    class CListner
    {
    public:
        using __SessionPtr = std::shared_ptr<CSession>;
        using AcceptorType = boost::asio::ip::tcp::acceptor;
        using EndpointType = boost::asio::ip::tcp::endpoint;
        using SocketType = boost::asio::ip::tcp::socket;

    public:
        CListner(std::function<__SessionPtr(SocketType)> session_factory,
                 const EndpointType& endpoint);
        ~CListner();
        
        void start_accept();


    private:
        std::function<__SessionPtr(SocketType)> session_factory_;
        AcceptorType acceptor_;

    };
}