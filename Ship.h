#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "GameObject.h"

//forward dec
class XpModule;

class Ship : public GameObject
{
    public:
        Ship(DataBank* t_pData);

        //stats
        double statShotCoolDown;
        double statShotSpeed;
        double statSpeed;
        int health;
        int maxHealth;

        void modifyHealth(int mod);
        bool shotCooledDown;
        double shotCoolDown;
        virtual void update(float elapsed);
        void startShotCoolDown();
};

#endif // SHIP_H_INCLUDED
