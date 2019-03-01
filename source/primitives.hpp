#ifndef SNAKE_PRIMS_H
#define SNAKE_PRIMS_H

struct Coord 
{
    int x;
    int y;
    Coord(){};
    Coord(int __x, int __y)
    {
        x = __x;
        y = __y;
    };
};

#endif