
#include <iostream>
#include <memory>

#include "server.hpp"

int main(int argc, char* argv[])
{
    try
    {
        if ( argc < 2 )
        {
            std::cerr << "Usage: <progam> <port>\n";
            return 1;
        }

        std::shared_ptr<server::CServer> server = std::make_shared<server::CServer>(std::atoi(argv[2]));
        
        server->run();


    } catch(std:: exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return 0;
}