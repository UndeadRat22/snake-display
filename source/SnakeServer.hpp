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
        int client_socket;

        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;

        unsigned int client_addr_len;

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

        ~SnakeServer()
        {
            dispose();
        };
        
        void dispose()
        {
            close(server_socket);
        };
};