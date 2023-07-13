
#include "pch.hpp"
#include "LDConnector.hpp"
#include "LDIOContext.hpp"

namespace net_core
{
    Connector::Connector(std::function<SessionPtr(SocketType)> session_factory,
                         const std::string& host, 
                         const std::string& port):
        session_factory_(session_factory), 
        resolver_(IOContext::instance().get_io_context()), 
        host_(host), port_(port), session_()
    {

    }

    Connector::~Connector()
    {
    }

    ErrCode Connector::connect()
    {        
        SocketType socket(IOContext::instance().get_io_context());

        ResolverType::iterator endpoint_iterator = resolver_.resolve(host_, port_);
        ResolverType::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
        
        while(error && endpoint_iterator != end)
        {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if(error)
            return eErrCodeHostNotFound;

        session_ = session_factory_(std::move(socket));
        session_->start();
        session_->on_connected();
        
        return 0;
    }
}