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

void clean_exit(int __s1, int __s2, int code)
{
    close(__s1);
    close(__s2);
    exit(code);
}

int main(int argc, char** argv)
{
    unsigned int port;
    int listen_socket;
    int client_socket;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    unsigned int client_addr_len;

    char buffer[BUFSIZE];

    int sent_len;
    int recv_len;

    if (argc != 2)
    {
        std::cout << "USAGE " << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    port = atoi(argv[1]);

    if ((port < 1) || (port > 65535))
    {
        std::cerr << "Invalid port specified, port := [1 : 65535]" << std::endl;
        exit(1);
    }

    if ((listen_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Cannot create a listening socket" << std::endl;
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    if (bind (listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Cannot bind listening socket." << std::endl;
        exit(1);
    }

    if (listen(listen_socket, 2) < 0)
    {
        std::cerr << "Cannot listen() using resource: " <<  listen_socket << " " << std::endl;
        clean_exit(listen_socket, 0, 1);
    }

    /*while (1)
    {
        memset(&server_addr, 0, sizeof(server_addr));
        memset(&buffer, 0, sizeof(buffer));
        if  ((client_socket = accept(listen_socket, (struct sockaddr*) &client_addr, &client_addr_len))< 0)
        {
            std::cerr << "Error occured when accepting a connection" << std::endl;
            clean_exit(client_socket, listen_socket, 1);
        }

        sent_len = recv(client_socket, buffer, sizeof(buffer), 0);
        if (sent_len < 1)
        {
            std::cout << "Failed to receive data from client" << std::endl;
            clean_exit(client_socket, listen_socket, 1);
        }
    }*/
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&buffer, 0, sizeof(buffer));
    if  ((client_socket = accept(listen_socket, (struct sockaddr*) &client_addr, &client_addr_len))< 0)
    {
        std::cerr << "Error occured when accepting a connection" << std::endl;
        clean_exit(client_socket, listen_socket, 1);
    }
    recv_len = recv(client_socket, buffer, sizeof(buffer), 0);
    if (recv_len < 1)
        clean_exit(client_socket, listen_socket, 1);
    if (recv_len == 2)
    {
        std::cout << (int)buffer[0] << " " << (int)buffer[1] << std::endl;
    }
    clean_exit(client_socket, listen_socket, 0);
}