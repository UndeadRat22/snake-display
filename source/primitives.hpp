#ifndef SNAKE_PRIMS_H
#define SNAKE_PRIMS_H

enum Direction 
{
    POS_X,
    NEG_X,
    POS_Y,
    NEG_Y
};

Direction opposite(const Direction& dir)
{
    switch (dir)
    {
        case POS_X:
            return NEG_X;
        case POS_Y:
            return NEG_Y;
        case NEG_X:
            return POS_X;
        case NEG_Y:
            return POS_Y;
        default:
            return POS_X;
    }
}

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