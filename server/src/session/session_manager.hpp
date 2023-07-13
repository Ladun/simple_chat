#pragma once

#include <map>

#include <LDServerEngine.hpp>

namespace server
{   
    // TODO: Change to Thread-safe singleton
    class SessionManager : public net_core::Singleton<SessionManager>
    {
    public:
        SessionManager() = default;
        ~SessionManager() = default;

        net_core::SessionPtr generate(net_core::SocketType socket);
        net_core::SessionPtr find(uint32_t id);
        void remove(net_core::SessionPtr session);

    private:
        std::shared_mutex mutex_;

        uint32_t session_id_;
        std::map<uint32_t, net_core::SessionPtr> session_list_;
        
    };
}