
#include "pch.hpp"
#include "LDListner.hpp"
#include "LDSession.hpp"
#include "LDIOContext.hpp"


namespace net_core
{

    CListner::CListner(std::function<SessionPtr(SocketType)> session_factory,
                       const EndpointType& endpoint) :
        session_factory_(session_factory_), acceptor_(CIOContext::instance().get_io_context(), endpoint)
    {
        start_accept();
    }

    CListner::~CListner()
    {
        
    }


    void CListner::start_accept()
    {        
        // 새로운 클라이언트의 연결을 받기 위해 비동기적으로 accept 작업을 수행합니다.
        SocketType socket(CIOContext::instance().get_io_context());
        acceptor_.async_accept(socket,
            [this, &socket](boost::system::error_code ec)
            {
                if (!ec)
                {
                    SessionPtr new_session = session_factory_(std::move(socket));
                    new_session->start();
                    new_session->on_connected();
                }

                // 다음 클라이언트의 연결을 기다립니다.
                start_accept();
            });
    }
}