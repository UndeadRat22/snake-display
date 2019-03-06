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
    public:
        void parse_mask(const char& mask)
        {
            std::cout << (int)mask << std::endl;
            state.c1_lost = 8 & mask;
            state.c2_lost = 4 & mask;
            state.c1_ate = 2 & mask;
            state.c2_ate = 1 & mask;
        };

        void print_state()
        {
            std::cout 
                << state.c1_lost << " "
                << state.c2_lost << " "
                << state.c1_ate << " "
                << state.c2_ate << "\n";
        }
};

#endif