#pragma once

#include <LDServerEngine.hpp>

namespace client
{
    class CClient
    {
    public:
        CClient(const std::string& nickname,
                const std::string& host,
                const std::string& port);
        ~CClient();

        net_core::ErrCode init();
        net_core::ErrCode connect_and_run();
        net_core::ErrCode close();
    
    private:

        void __io_context_run();

    private:
        bool is_init_;

        std::string nickname_;
        
        std::thread thread_;
        net_core::Connector connector_;
    };
}