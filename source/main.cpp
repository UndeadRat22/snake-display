#include "conutil.h"

#include "display.hpp"

#include <iostream>


int main(int argc, char** argv)
{
    Display* d = new Display(10, 10);
    char input;
    do 
    {
        input = getch();
        d->update(input);
        d->draw();
    } while (input != 'q');
    delete d;
    return -1;
}