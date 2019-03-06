#include "conutil.h"

#include "Game.hpp"
#include "ClientDisplay.hpp"

#include <iostream>


int main(int argc, char** argv)
{
    Game* g = new Game(10, 10, Coord(0,0), Coord(0, 5), Coord(5, 4));
    ClientDisplay* cd = new ClientDisplay();
    char input1, input2;
    do 
    {
        char result = g->update(input1, input2);
        cd->parse_mask(result);
        cd->print_state();
        g->draw();
        input1 = getch();
        input2 = getch();
    } while (input1 != 'q');
    delete g;
    delete cd;
}