#ifndef METER_H_INCLUDED
#define METER_H_INCLUDED

#include "Vector2d.h"
#include "Ship.h"

#include <SFML/Graphics.hpp>

class Meter
{
    public:
        Meter(Ship* t_pTarget);

        bool anchored;
        Ship *pTarget;
        Vector2d dims;
        Vector2d coords;
        sf::Shape bar;


        //functions
        bool update(sf::RenderWindow &win);
};

#endif // METER_H_INCLUDED
