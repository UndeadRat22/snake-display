
#include "snake_client.hpp"

#include <iostream>

#include <stdlib.h>
#include <string.h> //memset
#include <unistd.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "USAGE: " << argv[0] << " <ip> <port>" << std::endl;
        exit(0);
    }

    SnakeClient client;

    if (!client.set_port(argv[2]))
    {
        std::cerr << "Wrong port specified" << std::endl;
        exit(1);
    }
    std::cout << "creating_socket" << std::endl;
    if (!client.create_socket())
    {
        std::cerr << "Could not create socket!" << std::endl;
        exit(1);
    }

    if (!client.set_ip(argv[1]))
    {
        std::cerr << "Invalid remote IP address specified!" << std::endl;
        client.dispose();
        exit(1);
    }
    std::cout << "connecting to server" << std::endl;
    if (!client.connect_to_server())
    {
        std::cerr << "Could not connect (server down | wrong ip | wrong port)." << std::endl;
        client.dispose();
        exit(1);
    }
    // send height width info;
    int width, height;
    std::cout << "w / h" << std::endl;
    std::cin >> width >> height;

    std::cout << "buffering" << std::endl;
    client.buffer_byte((char) width);
    client.buffer_byte((char) height);
    std::cout << "sending" << std::endl;
    if (!client.send_message())
    {
        std::cerr << "Failed to send game info to server" << std::endl;
        client.dispose();
        exit(1);
    }
    if (!client.recv_message(2))
    {
        std::cerr << "Failed to get game info from server" << std::endl;
        client.dispose();
        exit(1);
    }
    else
    {
        std::cout << (int) (client.get_buffer() [0]) << std::endl;
    }
    client.dispose();
}