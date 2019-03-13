#include "snake_client.hpp"
#include "ClientDisplay.hpp"

#include "conutil.h"

#include <iostream>

#include <stdlib.h>
#include <string.h> //memset
#include <unistd.h>

int main(int argc, char** argv)
{
    if (argc != 5)
    {
        std::cout << "USAGE: " << argv[0] << " <ip> <port> <width> <height>" << std::endl;
        exit(0);
    }
    SnakeClient client;

    if (!client.set_port(argv[2]))
    {
        std::cerr << "Wrong port specified" << std::endl;
        exit(1);
    }
    //std::cout << "creating_socket" << std::endl;
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
    //std::cout << "connecting to server" << std::endl;
    if (!client.connect_to_server())
    {
        std::cerr << "Could not connect (server down | wrong ip | wrong port)." << std::endl;
        client.dispose();
        exit(1);
    }
    // send height width info;
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);
    
    //std::cout << "buffering" << std::endl;
    client.buffer_byte((char) width);
    client.buffer_byte((char) height);
    //std::cout << "sending" << std::endl;
    
    if (!client.send_message())
    {
        std::cerr << "Failed to send game info to server" << std::endl;
        client.dispose();
        exit(1);
    }
    if (!client.recv_message(3))
    {
        std::cerr << "Failed to get game info from server" << std::endl;
        client.dispose();
        exit(1);
    }
    //if we got the two bytes, then we have the display width and height 
    //(these can be different can be different from the rq ones)
    width = (int) (client.get_buffer()[0]);
    height = (int) (client.get_buffer()[1]);
    ClientDisplay display = ClientDisplay(width, height);
    display.is_snake1 = (bool) (client.get_buffer()[2]);
    display.is_init = false;
    char prev_input = 'a';
    while(true)
    {
        //2bytes s1-pos, 2bytes s2-pos, 2bytes fpos, 1 byte flags
        // 2 + 2 + 2 + 1 = 7
        if (!client.recv_message(7))
        {
            std::cerr << "Server did not respond, exiting" << std::endl;
            client.dispose();
            exit(1);
        }

        char* resp = client.get_buffer();
        
        Coord s1, s2, f;
        s1.x = (int) resp[0];
        s1.y = (int) resp[1];
        
        s2.x = (int) resp[2];
        s2.y = (int) resp[3];

        f.x = (int) resp[4];
        f.y = (int) resp[5];

        if (!display.is_init)
            display.init(s1, s2, f);
        else
            display.update(s1, s2, f);

        display.draw();

        // std::cout 
        //     << s1.x << " " << s1.y << "\n"
        //     << s2.x << " " << s2.y << "\n"
        //     << f.x << " " << f.y << "\n";
        // std::cout 
        //     << (display.is_snake1 ? "true" : "false") << "\n";
        display.parse_mask(resp[6]);
        //display.print_state();

        if (display.won())
        {
            std::cout << "you won!" << std::endl;
            break;
        }
        if (display.lost())
        {
            std::cout << "you lost!" << std::endl;
            break;
        }
        
        client.clear_buffer();
        char input;

        //std::cin >> input;
        //.7s
        input = getch(1000000);
        if (input == -1)
        {
            input = prev_input;
        }
        else 
        {
            prev_input = input;
        }

        client.buffer_byte(input);

        if (!client.send_message())
        {
            std::cerr << "Failed to send input to server" << std::endl;
            client.dispose();
            exit(1);
        }

    }
    client.dispose();
}