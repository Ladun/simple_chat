#include <iostream>
#include <boost/asio.hpp>

#include "client.hpp"


int main(int argc, char* argv[])
{

    try
    {
        if(argc != 4)
        {
            std::cerr << "Usage: client <nickname> <host> <port>\n";
            return 1;
        }
        
        client::CClient client(argv[1], argv[2], argv[3]);

        client.init();

        std::cout << "[Start Client]\n";
        net_core::ErrCode err = client.connect_and_run();
        if(err)
        {
            std::cout << err;
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}