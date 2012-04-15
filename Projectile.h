#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "GameObject.h"

class Projectile : public GameObject
{
    public:
        Projectile(DataBank* t_pData);
        void update(float elapsed);
};

#endif // PROJECTILE_H_INCLUDED
