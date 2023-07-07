#pragma once

#include "LDCore.hpp"
#include "LDBuffer.hpp"

#include <boost/asio.hpp>

namespace net_core
{
    // 세션 클래스 정의
    constexpr Size eSzPacketMin = sizeof(CBufferHeader);
    class CSession : public std::enable_shared_from_this<CSession>
    {
    public:
        using SocketType = boost::asio::ip::tcp::socket;	
    
    public:
        CSession(SocketType socket);
        virtual ~CSession();

        void start();
        void send(char* buffer, int size);

    private:
        ErrCode disconnect();    
        ErrCode register_recv();
        ErrCode on_recv(Size size);

    public:
        virtual void on_connected(/*endpoint*/) = 0;
        virtual int on_recv(/*Arraysegment<byte> buffer*/) = 0;
        virtual void on_send() = 0;
        virtual void on_disconnected() = 0;

    public: 
        SocketType& socket()
        {
            return socket_;
        }

    private:
        SocketType socket_;
        CBuffer buffer_;
        
    };
}