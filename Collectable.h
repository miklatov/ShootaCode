#ifndef COLLECTABLE_H_INCLUDED
#define COLLECTABLE_H_INCLUDED
#include "GameObject.h"

class Collectable : public GameObject
{
    public:
        Collectable(DataBank* t_pData);
        int value;
};

#endif // COLLECTABLE_H_INCLUDED
