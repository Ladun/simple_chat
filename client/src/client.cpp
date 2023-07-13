
#include <iostream>

#include "client.hpp"
#include "handler.hpp"
#include "session/server_session.hpp"

#include "custom_packet.hpp"

namespace client
{
    CClient::CClient(const std::string& nickname,
                     const std::string& host,
                     const std::string& port)
        :  connector_(
            [](net_core::SocketType socket) -> net_core::SessionPtr
            {
                return std::make_shared<ServerSession>(std::move(socket));
            },
            host, port), nickname_(nickname)
    {    
    }

    CClient::~CClient()
    {
        
    }

    net_core::ErrCode CClient::init()
    {
        // add handler;
        
        net_core::MessageHandler::instance().register_handler(
            static_cast<net_core::MessageNo>(net_packet::PacketCode::CHAT),
            &ChatPacketHandler);

        is_init_ = true;
        return 0;
    }

    net_core::ErrCode CClient::connect_and_run()
    {
        if(!is_init_)
            return eErrCodeNoInitialize;
            
        net_core::ErrCode err = connector_.connect();
        if(err)
            return err;

        // Run io_context -> run program
        thread_ = std::thread{std::bind(&CClient::__io_context_run, this)};
        
        // Custom update
        std::array<char, 1024> msg;
        while(true)
        {
            memset(msg.data(), '\0', msg.size());
            if(!std::cin.getline(msg.data(), 1024 - nickname_.size()))
            {
                std::cin.clear();
            }

            // TODO: Send Data   
            net_packet::ChatPacket packet{};
            packet.data = 1;
            
            connector_.get_session()->send<net_packet::ChatPacket>(packet);            
        }
        
        thread_.join();
    }

    net_core::ErrCode CClient::close()
    {
        
        net_core::IOContext::instance().stop();
        return 0;
    }

    void CClient::__io_context_run()
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