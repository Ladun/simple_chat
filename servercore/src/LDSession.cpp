
#include "pch.hpp"
#include "LDSession.hpp"
#include "LDHandler.hpp"
#include "LDIOContext.hpp"

namespace net_core
{

    CSession::CSession(SocketType socket) 
        : socket_(std::move(socket)), buffer_(eSzPacketMax)
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

    void CSession::send(char* buffer, int size)
    {
        socket_.async_write_some(boost::asio::mutable_buffer(buffer, size), CIOContext::instance().bind_executor(
			[this](const boost::system::error_code& pError, std::size_t pSendSize)
            {
                if(pError.value() != 0 || pSendSize == 0)
                    disconnect();
            })
        );
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
                if(pError.value() != 0)
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
            }));

    }

    ErrCode CSession::on_recv(Size size)
    {
        if(size == 0)
            return eErrCodeInvalidSize;

        if(!buffer_.on_push(size))
            return eErrCodeSessionBufferFull;

        Size    aSize = 0;
        ErrCode aResult = 0;
        char*   aData = buffer_.front(aSize, aResult);
        if(aResult != 0)
            return aResult;

        while(aData != nullptr && aResult == 0)
        {   
            if(aSize < sizeof(CPacketHeader))
                return eErrCodeInvalidSize;

            CPacketHeader* aHeader = reinterpret_cast<CPacketHeader*>(aData);
            aResult = CMessageHandler::instance().process(aHeader->message_, aHeader, aSize);
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