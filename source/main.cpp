#include "display.hpp"

int main(int argc, char** argv)
{
    Display* d = new Display(10, 10);
    d->draw();
    delete d;
    return -1;
}