#ifndef SNAKE_DATA_H
#define SNAKE_DATA_H

#include "primitives.hpp"
#include <vector>

class Snake 
{
    private:
        int speed_x = 0;
        int speed_y = 0;

        void update_speed()
        {
            switch (direction)
            {
                case POS_X:
                    {
                        speed_x = 1;
                        speed_y = 0;
                        break;
                    }
                case NEG_X:
                    {
                        speed_x = -1;
                        speed_y = 0;
                        break;
                    }
                case POS_Y:
                    {
                        speed_x = 0;
                        speed_y = 1;
                        break;
                    }
                case NEG_Y:
                    {
                        speed_x = 0;
                        speed_y = -1;
                        break;
                    }
                default:
                    break;
            }
        };
        Direction direction = POS_X;
    public:
        std::vector<Coord>* parts;

        Snake(Coord head)
        {
            parts = new std::vector<Coord>();
            parts->push_back(head);
            update_speed();
        };
        
        ~Snake()
        {
            delete parts;
        };

        bool set_direction(Direction dir)
        {
            if (dir != opposite(direction))
            {
                direction = dir;
                return true;
            }
            return false;
        }
        
        void move(const int& lim_x, const int& lim_y)
        {
            for (int i = parts->size(); i > 0; i--)
            {
                Coord next = parts->at(i - 1);
                (*parts)[i] = next;
            }
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