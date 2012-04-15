#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include "SFML/Window.hpp"

//forward dec
class Enemy;

class Ai
{
    public:
        Enemy* pOwner;
        sf::Clock clock;

        Ai(Enemy* t_pOwner);
        virtual void update()=0;
};

#endif // AI_H_INCLUDED
