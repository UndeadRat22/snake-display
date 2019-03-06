#ifndef SNAKE_SERVER_H
#define SNAKE_SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

#include <stdlib.h>
#include <string.h> //memset
#include <unistd.h>

#define BUFSIZE 1024

class SnakeServer
{
    private:
        char buffer[BUFSIZE];
        int filled = 0;

        unsigned int port;
        int listen_socket;
        int client1_socket;
        int client2_socket;

        struct sockaddr_in server_addr;
        struct sockaddr_in client1_addr;
        struct sockaddr_in client2_addr;

        unsigned int client1_addr_len;
        unsigned int client2_addr_len;

    public:
        bool create_listen_socket()
        {
            return !((listen_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0);
        };

        bool bind_listen_socket()
        {
            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
            server_addr.sin_port = htons(port);
            return !(bind (listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0);
        };

        bool set_port(char* __port)
        {
            port = atoi(__port);
            return !((port < 1) || (port > 65535));
        };

        bool listen_for_clients(const int& __n)
        {
            return (listen(listen_socket, __n) >= 0);
        };


        bool buffer_byte(const char& __byte)
        {
            if (filled >= BUFSIZE)
                return false;
            buffer[filled] = __byte;
            filled++;
            return true;
        };

        bool accept_clients()
        {
            memset(&server_addr, 0, sizeof(server_addr));
            memset(&buffer, 0, sizeof(buffer));
            client1_socket = accept(listen_socket, (struct sockaddr*) &client1_addr, &client1_addr_len);
            client2_socket = accept(listen_socket, (struct sockaddr*) &client2_addr, &client2_addr_len);
            return (client1_socket >= 0) || (client2_socket >= 0);
        };

        bool send_message()
        {
            int sent_len1 = send(client1_socket, buffer, filled, 0);    
            int sent_len2 = send(client2_socket, buffer, filled, 0);
            bool success = (sent_len1 == filled) && (sent_len1 == filled);
            filled = 0;
            return success;
        };

        bool recv_msg(const int& __size, const bool& c1 = true)
        {
            int recv_len = recv(c1 ? client1_socket : client2_socket, buffer, sizeof(buffer), 0);
            filled = recv_len;
            return recv_len > 0;
        };

        char* get_buffer()
        {
            return buffer;
        };

        ~SnakeServer()
        {
            dispose();
        };
        
        void dispose()
        {
            close(listen_socket);
            close(client1_socket);
            close(client2_socket);
        };
};

#endif