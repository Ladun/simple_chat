#pragma once

#include <LDServerEngine.hpp>

namespace ld_client
{
    enum class State
    {
        NOT_INITIALIZED,
        INITIALIZED, 
        RUNNING,
        CLOSED
    };

    class Client
    {
    public:
        Client(const std::string& nickname,
                const std::string& host,
                const std::string& port);
        ~Client();

        net_core::ErrCode init();
        net_core::ErrCode connect_and_run();
        net_core::ErrCode close();
    
    private:

        void __io_context_run();

    private:
        State state_;

        std::string nickname_;
        
        std::thread thread_;
        net_core::Connector connector_;
    };
}