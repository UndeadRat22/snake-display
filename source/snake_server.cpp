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
        std::cerr << "Error in recv, client1" << std::endl;
        server.dispose();
        exit(1);
    }

    if (!server.recv_msg(2, false))
    {
        std::cerr << "Error in recv, client2" << std::endl;
        server.dispose();
        exit(1);
    }
    int width, height;
    char* resp = server.get_buffer();
    width = (int) resp[0];
    height = (int) resp[1];
    //send w h is_snek1 to client1
    server.buffer_byte(1);

    if (!server.send_msg_c(true))
    {
        std::cerr << "failed to send msg" << std::endl;
        server.dispose();
        exit(1);
    }

    //send w h is_snek2 to client2
    server.unbuffer_byte();
    server.buffer_byte(0);

    if (!server.send_msg_c(false))
    {
        std::cerr << "failed to send msg" << std::endl;
        server.dispose();
        exit(1);
    }

    server.clear_buffer();

    //start game pretty much
    //s1 pos
    server.buffer_byte(5);
    server.buffer_byte(6);
    //s2 pos
    server.buffer_byte(7);
    server.buffer_byte(8);
    //f pos
    server.buffer_byte(4);
    server.buffer_byte(4);
    //flags
    server.buffer_byte(5);

    if (!server.send_msg_both())
    {
        std::cerr << "Can't send game info to clients!" << std::endl;
        server.dispose();
        exit(1);
    }

    //get input from clients
    //c1
    if (!server.recv_msg(1, true))
    {
        std::cerr << "Could not get user input from client1" << std::endl;
        server.dispose();
        exit(1);
    }
    //c2
    if (!server.recv_msg(1, false))
    {
        std::cerr << "Could not get user input from client1" << std::endl;
        server.dispose();
        exit(1);
    }

    server.dispose();
}