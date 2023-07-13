#pragma once

#include "LDCore.hpp"
#include "LDBuffer.hpp"
#include "LDPacketHeader.hpp"

#include <boost/asio.hpp>


namespace net_core
{
    // 세션 클래스 정의
    constexpr Size eSzPacketMin = sizeof(BufferHeader);
    
    class Session : public std::enable_shared_from_this<Session>
    {
    public:
        Session(SocketType&& socket);
        virtual ~Session();

        void start();
        template<typename PacketType>
        ErrCode send(PacketHeader& packet)
        {
            // Temp code.
            // Add to buffer_
            send_buffer_.clear();
            send_buffer_.push(reinterpret_cast<char*>(&packet), sizeof(PacketType));

            // Size    size = 0;
            // ErrCode result = 0;
            // char*   data = send_buffer_.front(size, result);
            // if(result)
            //     return result;

            send(send_buffer_.get_buffer(), send_buffer_.get_using_size());
            return 0;
        }
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
        Buffer buffer_;
        Buffer send_buffer_;
        
    };
    using SessionPtr = std::shared_ptr<Session>;
}