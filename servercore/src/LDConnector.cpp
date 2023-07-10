
#include "pch.hpp"
#include "LDConnector.hpp"
#include "LDIOContext.hpp"

namespace net_core
{
    CConnector::CConnector(const std::string& host, 
                           const std::string& port):
        resolver_(CIOContext::instance().get_io_context()), 
        host_(host), port_(port), session_(nullptr);
    {

    }

    CConnector::~CConnector()
    {
    }

    ErrCode CConnector::connect()
    {        
        SocketType socket(CIOContext::instance().get_io_context());

        ResolverType::iterator endpoint_iterator = resolver_.resolve(host_, port_);
        ResolverType::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
        
        while(error && endpoint_iterator != end)
        {
            socket->close();
            socket->connect(*endpoint_iterator++, error);
        }
        if(error)
            return eErrCodeHostNotFound;

        session_ = std::make_shared<CSession>(std::move(socket));
        session_->start();
        session_->on_connected();
        
        return 0;
    }
}