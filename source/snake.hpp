#ifndef SNAKE_DATA_H
#define SNAKE_DATA_H

#include "primitives.hpp"
#include <vector>

class Snake 
{
    private:
    std::vector<Coord>* parts;
    public:
    Snake()
    {
        parts = new std::vector<Coord>();
    };
    ~Snake()
    {
        delete parts;
    };

    Coord get_head()
    {
        return parts->at(0);
    };

    Coord get_tail()
    {
        return parts->at(parts->size() - 1);
    };
};

#endif