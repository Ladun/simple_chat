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
        CSession(SocketType socket);
        virtual ~CSession();

        void start();
        void send(char* buffer, int size);

    private:
        ErrCode disconnect();    
        ErrCode register_recv();
        ErrCode on_recv(Size size);

    public:
        virtual void on_connected() = 0;
        virtual void on_send(std::size_t sendSize) = 0;
        virtual void on_disconnected() = 0;

    public: 
        void set_id(uint32_t id) { id_ = id; }
        uint32_t get_id() const { return id_; }
        SocketType& socket()
        {
            return socket_;
        }

    protected:
        uint32_t id_{};
        SocketType socket_;
        CBuffer buffer_;
        
    };
    using SessionPtr = std::shared_ptr<CSession>;
}