#ifndef SNAKE_DATA_H
#define SNAKE_DATA_H

#include "primitives.hpp"
#include <queue>
#include <vector>
#include <iostream>

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
        Direction direction = NEG_X;
    public:
        std::vector<Coord>* parts;
        
        Snake(){};

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

        void eat(const Coord& c)
        {
            if (parts->size() == 1)
                parts->push_back( c );
            else
                parts->insert(parts->begin(), 1, c);
        }

        bool set_direction(Direction dir)
        {
            if (parts->size() == 1 || dir != opposite(direction))
            {
                direction = dir;
                update_speed(); 
                return true;
            }
            return false;
        };
        
        void move(const int& lim_x, const int& lim_y, const bool& __move_head = true)
        {
            for (unsigned int i = parts->size(); i > 0; i--)
            {
                Coord next = parts->at(i - 1);
                (*parts)[i] = next;
            }
            if (!__move_head)
                return;
            Coord head = get_head();
            (*parts)[0] = Coord((head.x + speed_x + lim_x) % lim_x, (head.y + speed_y + lim_y) % lim_y);
        };

        bool try_eat(const Coord& __food)
        {
            Coord head = get_head();
            if ((head.x == __food.x) && (head.y == __food.y))
            {
                eat(__food);
                return true;
            }
            return false;
        };

        bool is_dead(const Snake& other) const
        {
            Coord head = this->get_head();
            for (int i = 1; i < parts->size(); i ++){
                Coord c = (*parts)[i];
                if ((head.x == c.x) && (head.y == c.y))
                    return true;
            }
            for (auto c : ((*other.parts)))
            {
                if (c.x == head.x && c.y == head.y)
                    return true;
            }
            return false;
        };

        void add_part(const Coord& part)
        { 
            parts->push_back(part);
        };

        Coord get_head() const
        {
            return parts->at(0);
        };

        Coord get_tail() const
        {
            return parts->at(parts->size() - 1);
        };
};

#endif