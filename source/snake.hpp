#ifndef SNAKE_DATA_H
#define SNAKE_DATA_H

#include "primitives.hpp"
#include <vector>

class Snake 
{
    public:
        std::vector<Coord>* parts;
        
        Snake(Coord head)
        {
            parts = new std::vector<Coord>();
            parts->push_back(head);
        };
        
        ~Snake()
        {
            delete parts;
        };

        void add_part(const Coord& part)
        {
            parts->push_back(part);
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