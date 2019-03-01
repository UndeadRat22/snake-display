#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "primitives.hpp"
#include "snake.hpp"

#include <iostream>
#include <vector>

class Display 
{
    private:
        char* output;
    public:
        Coord display_size;
        Snake snake;
        char none = '.';
        char food = '*';
        char body = '3';
        char head = '@';
     

        Display(int x, int y)
        {
            display_size.x = x;
            display_size.y = y;
            //x + 1 for new lines in every line
            // + 1 for \n + \0 at the end of the thing
            output = new char[(x + 1) * y + 1];
        };

        ~Display()
        {
            delete output;
        };

        int index_from_coords(const int& x, const int& y)
        {
            return x + y + (display_size.x * y);
        };

        void update(){
            clear();
        };

        void clear(){
            for (int y = 0; y < display_size.y; y++)
            {
                for (int x = 0; x <= display_size.x; x++)
                {
                    if (x == display_size.x)
                        output[index_from_coords(x, y)] = '\n';
                    else
                        output[index_from_coords(x, y)] = none;
                }
            }
        };

        void draw() 
        {
            std::cout << output;
        };
};

#endif