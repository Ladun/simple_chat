#include "server.hpp"
#include "session/session_manager.hpp"

using boost::asio::ip::tcp;

namespace server
{
    CServer::CServer(int port)
        : listner_(
            [](tcp::socket socket) -> std::shared_ptr<net_core::CSession>
            {
                return CSessionManager::instance().generate(std::move(socket));
            }, tcp::endpoint(tcp::v4(), port))
    {
    }

    CServer::~CServer()
    {
        
    }

    void CServer::run()
    {

    }
}