
#include "session_manager.hpp"
#include "client_session.hpp"

#include <iostream>

namespace server
{
    net_core::SessionPtr SessionManager::generate(net_core::SocketType socket)
    {
        net_core::WriteLock lock(mutex_);

        int session_id = ++session_id_;
        net_core::SessionPtr session = std::make_shared<ClientSession>(std::move(socket));
        session->set_id(session_id);

        session_list_.emplace(session_id, session);

        return session;
    }

    net_core::SessionPtr SessionManager::find(uint32_t id)
    {
        net_core::ReadLock lock(mutex_);
        auto iter = session_list_.find(id);
        if(iter == session_list_.end())
            return nullptr;

        return iter->second;
    }

    void SessionManager::remove(net_core::SessionPtr session)
    {
        net_core::WriteLock lock(mutex_);

    }

}