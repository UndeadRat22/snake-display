#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "primitives.hpp"
#include "snake.hpp"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

class Game
{
    private:
        char* output;
    public:
        Coord display_size;
        Coord food_pos;
        Snake* snake1;
        Snake* snake2;
        char none = '.';
        char food = '*';
        char body = '3';
        char head = '@';
     
        Game(int x, int y, Coord s1, Coord s2, Coord f)
        {
            srand(time(0));
            display_size.x = x;
            display_size.y = y;
            //x + 1 for new lines in every line
            // + 1 for \n + \0 at the end of the thing
            output = new char[(x + 1) * y + 1];
            snake1 = new Snake(s1);
            snake2 = new Snake(s2);
            food_pos = f;
        };

        ~Game()
        {
            delete output;
            delete snake1;
            delete snake2;
        };

        int index_from_coords(const int& x, const int& y)
        {
            return x + y + (display_size.x * y);
        };

        char update(const char& input1, const char& input2){
            clear();
            switch (input1)
            {
                case 'a':
                    snake1->set_direction(NEG_X);
                    break;
                case 'd':
                    snake1->set_direction(POS_X);
                    break;    
                case 'w':
                    snake1->set_direction(NEG_Y);
                    break;
                case 's':
                    snake1->set_direction(POS_Y);
                    break;
                default:
                    break;
            }
            switch (input2)
            {
                case 'a':
                    snake2->set_direction(NEG_X);
                    break;
                case 'd':
                    snake2->set_direction(POS_X);
                    break;    
                case 'w':
                    snake2->set_direction(NEG_Y);
                    break;
                case 's':
                    snake2->set_direction(POS_Y);
                    break;
                default:
                    break;
            }
            bool s1_ate = snake1->try_eat(food_pos);
            bool s2_ate = snake2->try_eat(food_pos);
            
            bool s1_dead = snake1->is_dead(*snake2);
            bool s2_dead = snake2->is_dead(*snake1);
            

            snake1->move(display_size.x, display_size.y);
            snake2->move(display_size.x, display_size.y);
            
            draw_snake(*snake1);
            draw_snake(*snake2);
            
            return make_mask(s1_ate, s2_ate, s1_dead, s2_dead);
        };

        char make_mask(const bool& __s1a, const bool& __s2a, const bool& __s1d, const bool& __s2d)
        {
            char mask = 0;
            mask |= __s1d ? 8 : 0;
            mask |= __s2d ? 4 : 0;
            mask |= __s1a ? 2 : 0;
            mask |= __s2a ? 1 : 0;
            return mask;
        };

        Coord random_coords()
        {
            int rand_x = rand() % display_size.x;
            int rand_y = rand() % display_size.y;
            return Coord(rand_x, rand_y);
        };

        void draw_snake(const Snake& __snake)
        {
            for (auto c : *__snake.parts)
            {
                output[index_from_coords(c.x, c.y)] = body;
            }
            Coord h = __snake.get_head();
            output[index_from_coords(h.x, h.y)] = head;
        };

        //could be done way easier, but was doing some testin :D
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
            //draw food
            output[index_from_coords(food_pos.x, food_pos.y)] = food;
        };

        void draw() 
        {
            std::cout << output;
        };
};

#endif