#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Ship.h"

class Player : public Ship
{
    public:
        Player(DataBank* t_pData);

        XpModule* pXp;

};



#endif // PLAYER_H_INCLUDED
