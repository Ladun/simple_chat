#pragma once

#include <LDServerEngine.hpp>

#include "session/session_manager.hpp"

namespace ld_server
{
    class Server
    {
    public:
        Server(int port);
        ~Server();

        net_core::ErrCode init();
        net_core::ErrCode run();
        net_core::ErrCode close();

        void broadcast(net_core::PacketHeader& packet, net_core::Size size);
    private:
        // template<typename PacketType>
        // void __send(/*session_id, data*/);
        void __io_context_run();

    private:
        bool is_init_;

        net_core::Listner listner_;

        unsigned int thread_cnt_;
        std::vector<std::thread> thread_list_;

    };
}