#include "display.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    Display* d = new Display(10, 10);
    d->update();
    d->draw();

    delete d;
    return -1;
}