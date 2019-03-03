/*
* unix socket stuff
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

#include <stdlib.h>
#include <string.h> //memset
#include <unistd.h>

#define BUFSIZE 1024

void clean_exit(int __s1, int code)
{
    close(__s1);
    exit(code);
}

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

    if (!client.connect_to_server())
    {
        std::cerr << "Could not connect (server down | wrong ip | wrong port)." << std::endl;
        client.dispose();
        exit(1);
    }
    // send height width info;
    int width, height;
    std::cin >> width >> height;
    //send 2 bytes w / h
    buffer[0] = (char) width;
    buffer[1] = (char) height;
    int sent_l = send(server_socket, buffer, 2, 0);
    if (sent_l < 1)
    {
        std::cerr << "Failed to send game info to server" << std::endl;
        clean_exit(server_socket, 1);
    }
    int recv_l = recv(server_socket, buffer, 2, 0);
    if ((recv_l < 1) || ((int) buffer[0] != width) || ((int) buffer[1] != height))
    {
        std::cerr << "Failed to get game info from server" << std::endl;
        clean_exit(server_socket, 1);
    }
    else
    {
        std::cout << "les go" << std::endl;
    }
    clean_exit(server_socket, 0);
}