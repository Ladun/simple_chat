
#include "pch.hpp"
#include "LDSession.hpp"
#include "LDHandler.hpp"
#include "LDIOContext.hpp"

namespace net_core
{

    Session::Session(SocketType&& socket) 
        : socket_(std::move(socket)), buffer_(eSzPacketMax), send_buffer_(eSzPacketMax)
    {
    }

    Session::~Session()
    {
        
    }

    void Session::start()
    {
        register_recv();
    }
    
    ErrCode Session::disconnect()
    {
        boost::system::error_code aError;

        on_disconnected();

        if(socket_.is_open())
            socket_.close(aError);

        return aError.value();
    }

    void Session::send(char* buffer, int size)
    {
        socket_.async_write_some(boost::asio::mutable_buffer(buffer, size), IOContext::instance().bind_executor(
			[this](const boost::system::error_code& ec, std::size_t send_size)
            {
                if(ec.value() != 0 || send_size == 0)
                {
                    std::cout << "Fail to send, error: "<< ec.message() <<"\n";
                    disconnect();
                }

                on_send(send_size);
            })
        );
    }

    ErrCode Session::register_recv()
    {
        Size size       = buffer_.get_usable_size();
        char* write_ptr = buffer_.get_write_ptr();

        if(size <  eSzPacketMin || buffer_.get_buffer_size() < size) 
        {
            disconnect();
            return eErrCodeSesBufferFull;
        }

        socket_.async_read_some(boost::asio::mutable_buffer(write_ptr, size), IOContext::instance().bind_executor(
            [this](const boost::system::error_code& ec, std::size_t recv_size)
            {
                
                if(ec.value() != 0)
                {
                    std::cout << "Fail to recv, error: "<< ec.message() <<"\n";
                    disconnect();
                    return;
                }

                ErrCode aErr = on_recv(static_cast<Size>(recv_size));
                if (aErr != 0)
                {
                    std::cout << "Fail on_recv, error: "<< aErr <<"\n";
                    disconnect();
                    return;
                }

                register_recv();
            }));
        
        return 0;
    }

    ErrCode Session::on_recv(Size size)
    {
        if(size == 0)
        {
            return eErrCodeInvalidSize;
        }

        if(!buffer_.on_push(size))
        {
            return eErrCodeSessionBufferFull;
        }


        Size    aSize = 0;
        ErrCode aResult = 0;
        char*   aData = buffer_.front(aSize, aResult);
        if(aResult != 0)
            return aResult;

        while(aData != nullptr && aResult == 0)
        {   
            if(aSize < sizeof(PacketHeader))
            {
                return eErrCodeInvalidSize;
            }

            PacketHeader* aHeader = reinterpret_cast<PacketHeader*>(aData);
            aResult = MessageHandler::instance().process(aHeader->message_, aHeader, aSize, this);
            if(aResult != 0)
                break;
            
            aData = buffer_.front(aSize, aResult);
        }
        if(aResult != 0)
            return aResult;

        buffer_.pop();
        return 0;
    }

    
} // namespace net_core