#ifndef SNAKE_CLIENT_H
#define SNAKE_CLIENT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

#include <stdlib.h>
#include <string.h> //memset
#include <unistd.h>

#define BUFSIZE 1024

struct reply 
{
    int msg_size;
    char* content;
};

class SnakeClient
{
    private:
        char buffer[BUFSIZE];
        int filled = 0;

        unsigned int port;
        struct sockaddr_in server_addr;
        int server_socket;
        
        int sent_len;
        int recv_len;
    public:
        bool create_socket()
        {
            return !((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0);
        };

        bool set_port(char* __port)
        {
            port = atoi(__port);
            return !((port < 1) || (port > 65535));
        };

        bool set_ip(char* __ip)
        {
            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(port);

            return !(inet_aton(__ip, &server_addr.sin_addr) <= 0);
        };

        bool connect_to_server()
        {
            return !(connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0);
        };

        bool buffer_byte(const char& __byte)
        {
            if (filled >= BUFSIZE)
                return false;
            buffer[filled] = __byte;
            filled++;
            return true;
        };

        bool send_message()
        {
            sent_len = send(server_socket, buffer, filled, 0);    
            bool success = sent_len == filled;
            filled = 0;
            return success;
        };

        bool recv_message(int __size)
        {
            std::cout << "recv.." << std::endl;
            recv_len = recv(server_socket, buffer, __size, 0);
            std::cout << "finished" << std::endl;
            return recv_len == __size;
        };

        char* get_buffer()
        {
            return buffer;
        };

        ~SnakeClient()
        {
            dispose();
        };
        
        void dispose()
        {
            close(server_socket);
        };
};

#endif