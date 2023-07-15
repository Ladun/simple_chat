#pragma once

#include <map>

#include <LDServerEngine.hpp>

namespace ld_server
{   
    class Server; 

    // TODO: Change to Thread-safe singleton
    class SessionManager : public net_core::Singleton<SessionManager>
    {
    public:
        SessionManager() = default;
        ~SessionManager() = default;

        net_core::SessionPtr generate(net_core::SocketType socket, Server* server);
        net_core::SessionPtr find(uint32_t id);
        void remove(net_core::SessionPtr session);

    public:
        std::map<uint32_t, net_core::SessionPtr>& get_session_list()
        {
            return session_list_;
        }

    private:
        std::shared_mutex mutex_;

        uint32_t session_id_;
        std::map<uint32_t, net_core::SessionPtr> session_list_;
        
    };
}