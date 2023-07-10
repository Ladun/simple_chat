
#include "client.hpp"

namespace client
{
    CClient::CClient(const std::string& host,
                    const std::string& port)
        :  connector(host, port)
    {    
    }

    CClient:~CClient()
    {
        
    }

    net_core::ErrCode CClient::init()
    {
        // add handler;


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

        thread_ = std::thread{std::bind(&CServer::__io_context_run, this)};
        
        std::array<char, 1024> msg;
        while(true)
        {
            memset(msg.data(), '\0', msg.size());
            if(!std::cin.getline(msg.data(), MAX_IP_PACK_SIZE - PADDING - MAX_NICKNAME))
            {
                std::cin.clear();
            }
            // TODO: Send Data   
            
        }
        
        thread_.join();
    }

    net_core::ErrCode CClient::send()
    {

    }

    net_core::ErrCode CClient::close()
    {
        
        net_core::CIOContext::instance().stop();
        return 0;
    }

    void CClient::__io_context_run()
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