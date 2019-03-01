#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "primitives.hpp"

#include <iostream>
#include <vector>

class Display 
{
    private:
        char* output;
        std::vector<Coord> body;

    public:
        Coord display_size;
        char clear = '.';
        char food = '*';
        char body = '3';
        char head = '@';
     

        Display(int x, int y)
        {
            display_size.x = x;
            display_size.y = y;
            output = new char[x * y + 2];
        };

        ~Display()
        {
            delete output;
        }

        void update(){

        }

        void draw() 
        {
            for (int y = 0; y < display_size.y; y++)
            {
                for (int x = 0; x < display_size.x; x++)
                {
                    std::cout << clear;
                }
                std::cout << std::endl;
            }
        };

        void redraw()
        {

        };
};


#endif