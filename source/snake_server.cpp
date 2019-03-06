#include "SnakeServer.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "USAGE " << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    SnakeServer server;
    if (!server.set_port(argv[1]))
    {
        std::cerr << "Invalid port specified, port := [1 : 65535]" << std::endl;
        exit(1);
    }

    if (!server.create_listen_socket())
    {
        std::cerr << "Cannot create a listening socket" << std::endl;
        exit(1);
    }

    if (!server.bind_listen_socket())
    {
        std::cerr << "Cannot bind the listen socket" << std::endl;
        server.dispose();
        exit(1);
    }

    if (!server.listen_for_clients(2))
    {
        std::cerr << "error when listening for clients" << std::endl;
        server.dispose();
        exit(1);
    }

    if  (!server.accept_clients())
    {
        std::cerr << "Error occured when accepting a connection" << std::endl;
        server.dispose();
        exit(1);
    }

    if (!server.recv_msg(2, true))
    {
        std::cerr << "Error in recv" << std::endl;
        server.dispose();
        exit(1);
    }
    
    if (!server.send_message())
    {
        std::cerr << "failed to send msg" << std::endl;
        server.dispose();
        exit(1);
    }
    
    server.dispose();
}