#include <iostream>
#include <boost/asio.hpp>

#include <protocol.hpp>
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

        boost:asio:io_context io_context;

        Client client(io_context, argv[1], argv[2], argv[3]);

        std::array<char, MAP_IP_PACK_SIZE> msg;
        while(true)
        {
            memset(msg.data(), '\0', msg.size());
            if(!std::cin.getline(msg.data(), MAX_IP_PACK_SIZE - PADDING - MAX_NICKNAME))
            {
                std::cin.clear();
            }
            // Send Data           
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}