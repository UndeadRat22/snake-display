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
    unsigned int port;
    int server_socket;

    struct sockaddr_in server_addr;

    unsigned int client_addr_len;

    char buffer[BUFSIZE];

    int sent_len;
    int recv_len;

    if (argc != 3)
    {
        std::cout << "USAGE: " << argv[0] << " <ip> <port>" << std::endl;
        exit(1);
    }

    port = atoi(argv[2]);

    if ((port < 1) || (port > 65535))
    {
        std::cerr << "Invalid port specified, port := [1 : 65535]" << std::endl;
        exit(1);
    }

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Cannot create a server socket" << std::endl;
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_aton(argv[1], &server_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid remote IP address" << std::endl;
        clean_exit(server_socket, 1);
    }

    if (connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Could not connect (server down | wrong ip | wrong port)." << std::endl;
        clean_exit(server_socket, 1);
    }
    int width, height;
    std::cin >> width >> height;
    //send 2 bytes w / h
    buffer[0] = (char) width;
    buffer[1] = (char) height;
    send(server_socket, buffer, 2, 0);
}