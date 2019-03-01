#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "primitives.hpp"

#include <iostream>
#include <vector>

class Display 
{
    private:
        char* output;
        std::vector<Coord> parts;

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
            //x + 1 for new lines in every line
            // + 2 for \n + \0 at the end of the thing
            output = new char[(x + 1) * y + 2];
        };

        ~Display()
        {
            delete output;
        }

        void update(){

        }

        void draw() 
        {
            std::cout << output;
        };

        void redraw()
        {

        };
};

#endif