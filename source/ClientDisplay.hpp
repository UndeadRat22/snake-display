#ifndef SNAKEC_DISPLAY_H
#define SNAKEC_DISPLAY_H

#include "primitives.hpp"
#include "snake.hpp"

#include <iostream>

struct GameState 
{
    bool c1_lost;
    bool c2_lost;
    bool c1_ate;
    bool c2_ate;
};

class ClientDisplay
{
    private:
        GameState state;
        Coord display_size;
        Coord food_pos;
        Snake* snake1;
        Snake* snake2;
        char none = '.';
        char food = '*';
        char body = '3';
        char head = '@';
        char* output;
    public:
        bool is_snake1;
        bool is_init;
        ClientDisplay(const int& __w, const int& __h)
        {
            display_size = Coord(__w, __h);
            output = new char[(__w + 1) * __h + 1];
            is_init = false;
        };
        ClientDisplay(const int& __w, const int& __h, Coord __s1p, Coord __s2p, Coord fp)
        {
            display_size = Coord(__w, __h);
            output = new char[(__w + 1) * __h + 1];
            snake1 = new Snake(__s1p);
            snake2 = new Snake(__s2p);
            food_pos = fp;
            is_init = true;
        };

        void init(Coord __s1p, Coord __s2p, Coord fp)
        {
            snake1 = new Snake(__s1p);
            snake2 = new Snake(__s2p);
            food_pos = fp;
            is_init = true;
        }

        ~ClientDisplay()
        {
            delete output;
            delete snake1;
            delete snake2;
        };

        

        void parse_mask(const char& __mask)
        {
            state.c1_lost = 8 & __mask;
            state.c2_lost = 4 & __mask;
            state.c1_ate = 2 & __mask;
            state.c2_ate = 1 & __mask;
        };

        void print_state()
        {
            std::cout 
                << state.c1_lost << " "
                << state.c2_lost << " "
                << state.c1_ate << " "
                << state.c2_ate << "\n";
        };

        void update(const Coord& __c1, const Coord& __c2, const Coord& __fpos)
        {
            if (state.c1_ate)
                snake1->eat(food_pos);
            if (state.c2_ate)
                snake2->eat(food_pos);
            
            snake1->move(display_size.x, display_size.y, false);
            (*(snake1->parts))[0] = __c1;
            snake2->move(display_size.x, display_size.y, false);
            (*(snake2->parts))[0] = __c2;
            
            food_pos = __fpos;
            clear();
            
            draw_snake(*snake1);
            draw_snake(*snake2);

            output[index_from_coords(food_pos.x, food_pos.y)] = food;
            Coord h1 = snake1->get_head();
            Coord h2 = snake2->get_head();
            output[index_from_coords(h1.x, h1.y)] = head;
            output[index_from_coords(h2.x, h2.y)] = head;
        };

        bool won()
        {
            return (is_snake1 && !state.c1_lost && state.c2_lost) 
                || (!is_snake1 && !state.c2_lost && state.c1_lost);
        };

        bool lost()
        {
            return is_snake1 ? state.c1_lost : state.c2_lost;
        };

        int index_from_coords(const int& x, const int& y)
        {
            return x + y + (display_size.x * y);
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