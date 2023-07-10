#include "server.hpp"
#include "session/session_manager.hpp"

namespace server
{
    CServer::CServer(int port)
        : listner_(
            [](net_core::SocketType) -> net_core::SessionPtr
            {
                return CSessionManager::instance().generate(std::move(socket));
            }, net_core::EndpointType(tcp::v4(), port)),
          thread_cnt_(0), is_init_(false)
    {
        thread_cnt_ = std::thread::hardware_concurrency() * 2;
    }

    CServer::~CServer()
    {
        
    }

    net_core::ErrCode CServer::init()
    {

        // add handler;

        is_init_ = true;
        return 0;
    }

    net_core::ErrCode CServer::run()
    {
        if(!is_init_)
            return eErrCodeNoInitialize;

        for (unsigned int index = 0; index < thread_cnt_; ++index)
        {
            thread_list_.emplace_back(std::thread{std::bind(&CServer::__io_context_run, this)});

        }

        // Server loop add;


        for(auto& aThread: thread_list_)
        {
            aThread.join();
        }

        return 0;
    }

    net_core::ErrCode CServer::close()
    {
        listner_.close();

        net_core::CIOContext::instance().stop();
        return 0;
    }

    void CServer::__io_context_run()
    {
        try
        {
            net_core::CIOContext::instance().run();
        } catch(std::exception& exception)
        {
            // TODO: log error;
        }
    }
}