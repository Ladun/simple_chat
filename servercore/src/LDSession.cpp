
#include "pch.hpp"
#include "LDSession.hpp"
#include "LDIOContext.hpp"

namespace net_core
{

    CSession::CSession(SocketType socket) 
        : socket_(std::move(socket))
    {
    }

    CSession::~CSession()
    {

    }

    void CSession::start()
    {

        register_recv();
    }
    ErrCode CSession::disconnect()
    {
        boost::system::error_code aError;
        if(socket_.is_open())
            socket_.close(aError);

        return aError.value();
    }

    void CSession::send()
    {
        // boost::asio::async_write(socket_,
        //                          )
    }

    ErrCode CSession::register_recv()
    {
        Size size       = buffer_.get_usable_size();
        char* write_ptr = buffer_.get_write_ptr();

        if(size <  eSzPacketMin || buffer_.get_buffer_size() < size) 
        {
            disconnect();
            return eErrCodeSesBufferFull;
        }

        socket_.async_read_some(boost::asio::mutable_buffer(write_ptr, size), CIOContext::instance().bind_executor(
            [this](const boost::system::error_code& pError, std::size_t pRecvSize)
            {
                if(pError.value() != 0 || pRecvSize == 0)
                {
                    disconnect();
                    return;
                }

                ErrCode aErr = on_recv(static_cast<Size>(pRecvSize));
                if (aErr != 0)
                {
                    disconnect();
                    return;
                }

                register_recv();
        ));
        
    }

    ErrCode CSession::on_recv(Size size)
    {
        
    }

    
} // namespace net_core