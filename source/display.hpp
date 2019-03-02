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
        Snake snake = Snake(Coord(0, 0));
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
            snake.add_part(Coord(1, 0));
            snake.add_part(Coord(2, 0));
            snake.add_part(Coord(3, 0));
        };

        ~Display()
        {
            delete output;
        };

        int index_from_coords(const int& x, const int& y)
        {
            return x + y + (display_size.x * y);
        };

        void update(const char& input){
            clear();
            switch (input)
            {
                case 'a':
                    snake.set_direction(NEG_X);
                    break;
                case 'd':
                    snake.set_direction(POS_X);
                    break;    
                case 'w':
                    snake.set_direction(NEG_Y);
                    break;
                case 's':
                    snake.set_direction(POS_Y);
                    break;
                default:
                    break;
            }
            snake.move(display_size.x, display_size.y);
            
            draw_snake(snake);
        };

        void draw_snake(Snake& __snake)
        {
            for (int i = 0; i < __snake.parts->size(); i++)
            {
                Coord c = __snake.parts->at(i);
                output[index_from_coords(c.x, c.y)] = body;
            }
            Coord h = __snake.get_head();
            output[index_from_coords(h.x, h.y)] = head;
        }

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