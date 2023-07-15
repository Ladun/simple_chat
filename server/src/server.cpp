

#include "server.hpp"
#include "handler.hpp"
#include "session/session_manager.hpp"

#include "custom_packet.hpp"


namespace ld_server
{
    Server::Server(int port)
        : listner_(
            [this](net_core::SocketType socket) -> net_core::SessionPtr
            {
                return SessionManager::instance().generate(std::move(socket), this);
            }, net_core::EndpointType(boost::asio::ip::tcp::v4(), port)),
          thread_cnt_(0), is_init_(false)
    {
        thread_cnt_ = std::thread::hardware_concurrency() * 2;
    }

    Server::~Server()
    {
        
    }

    net_core::ErrCode Server::init()
    {

        // add handler;
        
        net_core::MessageHandler::instance().register_handler(
            static_cast<net_core::MessageNo>(net_packet::PacketCode::CHAT),
            std::bind(&ChatPacketHandler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, this));

        is_init_ = true;
        return 0;
    }

    net_core::ErrCode Server::run()
    {
        if(!is_init_)
            return eErrCodeNoInitialize;

        for (unsigned int index = 0; index < thread_cnt_; ++index)
        {
            thread_list_.emplace_back(std::thread{std::bind(&Server::__io_context_run, this)});

        }

        // Server loop add;


        for(auto& aThread: thread_list_)
        {
            aThread.join();
        }

        return 0;
    }

    net_core::ErrCode Server::close()
    {
        listner_.close();

        net_core::IOContext::instance().stop();
        return 0;
    }

    void Server::broadcast(net_core::PacketHeader& packet, net_core::Size size)
    {
        for(const auto& [id, session] : SessionManager::instance().get_session_list())
        {
            if(session->socket().is_open())
            {
                session->send(packet, size);
            }
        }
    }

    void Server::__io_context_run()
    {
        try
        {
            net_core::IOContext::instance().run();
        } catch(std::exception& exception)
        {
            // TODO: log error;
        }
    }
}