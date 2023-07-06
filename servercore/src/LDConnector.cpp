
#include "pch.hpp"
#include "LDConnector.hpp"
#include "LDIOContext.hpp"

namespace net_core
{
    CConnector::CConnector(std::function<__SessionPtr(SocketType)> session_factory,
                           const std::string& host, 
                           const std::string& port):
        session_factory_(session_factory_), 
        resolver_(CIOContext::instance().get_io_context()), endpoint_iterator_(resolver_.resolve(host, port))
    {

    }

    CConnector::~CConnector()
    {
    }

    void CConnector::start_connect()
    {
        SocketType socket(CIOContext::instance().get_io_context());

        socket.async_connect(*endpoint_iterator_,
            [this, &socket](boost::system::error_code ec)
            {
                if (!ec)
                {
                    __SessionPtr new_session = session_factory_(std::move(socket));
                    new_session->start();
                }
                else
                {
                    // 예외처리
                }
            }
        );
    }
}