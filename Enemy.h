#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Ship.h"

//forward dec
class Ai;

class Enemy : public Ship
{
    public:
        Ai* pAi;

        Enemy(DataBank* t_pData);
        void update(float elapsed);
};

#endif // ENEMY_H_INCLUDED
