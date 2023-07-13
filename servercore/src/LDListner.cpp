
#include "pch.hpp"
#include "LDListner.hpp"
#include "LDSession.hpp"
#include "LDIOContext.hpp"

#include <iostream>


namespace net_core
{

    Listner::Listner(std::function<SessionPtr(SocketType)> session_factory,
                       const EndpointType& endpoint) :
        session_factory_(session_factory), acceptor_(IOContext::instance().get_io_context(), endpoint)
    {

		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        start_accept();
    }

    Listner::~Listner()
    {
        
    }


    void Listner::start_accept()
    {        
        // 새로운 클라이언트의 연결을 받기 위해 비동기적으로 accept 작업을 수행합니다.

        SocketType socket(IOContext::instance().get_io_context());
        SessionPtr new_session = session_factory_(std::move(socket));
        
        acceptor_.async_accept(new_session->socket(),
            [this, session=new_session.get()](boost::system::error_code ec)
            {
                if (!ec)
                {
                    // SessionPtr new_session = session_factory_(std::move(socket));
                    session->start();
                    session->on_connected();
                }
                else{
                    std::cout << "Fail to accept, error: "<< ec.message() <<"\n";
                }

                // 다음 클라이언트의 연결을 기다립니다.
                start_accept();
            });
    }

    ErrCode Listner::close()
    {
		boost::system::error_code aError;
		acceptor_.close(aError);
		return aError.value();
    }
}