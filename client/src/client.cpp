
#include <iostream>

#include "client.hpp"
#include "handler.hpp"
#include "session/server_session.hpp"

#include "custom_packet.hpp"

namespace ld_client
{
    Client::Client(const std::string& nickname,
                     const std::string& host,
                     const std::string& port)
        :  connector_(
            [this](net_core::SocketType socket) -> net_core::SessionPtr
            {
                return std::make_shared<ServerSession>(std::move(socket), this);
            },
            host, port), nickname_(nickname), state_(State::NOT_INITIALIZED)
    {    
    }

    Client::~Client()
    {
        
    }

    net_core::ErrCode Client::init()
    {
        // add handler;
        
        net_core::MessageHandler::instance().register_handler(
            static_cast<net_core::MessageNo>(net_packet::PacketCode::CHAT),
            &ChatPacketHandler);

        state_ = State::INITIALIZED;
        return 0;
    }

    net_core::ErrCode Client::connect_and_run()
    {
        if(state_ == State::NOT_INITIALIZED)
            return eErrCodeNoInitialize;
            
        net_core::ErrCode err = connector_.connect();
        if(err)
            return err;

        state_ = State::RUNNING;
        // Run io_context -> run program
        thread_ = std::thread{std::bind(&Client::__io_context_run, this)};
        
        // Custom update
        std::array<char, 992> msg;
        net_packet::ChatPacket packet{};
        memcpy(packet.nickname.data(), nickname_.data(), sizeof(nickname_.data()));
        while(true)
        {
            memset(msg.data(), '\0', msg.size());
            if(!std::cin.getline(msg.data(), 1024 - nickname_.size() - sizeof(net_core::PacketHeader)))
            {
                std::cin.clear();
            }

            if(state_ != State::RUNNING)
                break;

            memcpy(packet.message.data(), msg.data(), msg.size());
            
            connector_.get_session()->send(packet, sizeof(packet));            
        }
        thread_.join();

        return 0;
    }

    net_core::ErrCode Client::close()
    {
        
        net_core::IOContext::instance().stop();

        state_ = State::CLOSED;
        return 0;
    }

    void Client::__io_context_run()
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