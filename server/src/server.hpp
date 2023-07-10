#pragma once

#include <LDServerEngine.hpp>

namespace server
{
    class CServer
    {
    public:
        CServer(int port);
        ~CServer();

        net_core::ErrCode init();
        net_core::ErrCode run();
        net_core::ErrCode close();

    private:
        void __broadcast(/* data */);
        void __send(/*session_id, data*/);
        void __io_context_run();

    private:
        bool is_init_;

        net_core::CListner listner_;

        unsigned int thread_cnt_;
        std::vector<std::thread> thread_list_;

    };
}