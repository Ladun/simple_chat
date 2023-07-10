#pragma once

namespace net_core
{
    class CConnector
    {

    public:
        CConnector(const std::string& host, 
                   const std::string& port);
        ~CConnector();

        ErrCode connect();

        SessionPtr get_session() const{
            return session_;
        }
    
    private:
        SessionPtr session_;

        std::string& host_;
        std::string& port_;
        ResolverType resolver_;
    };
}