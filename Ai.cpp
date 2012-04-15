#include "Ai.h"
#include "Enemy.h"
#include <iostream>

Ai::Ai(Enemy* t_pOwner) : pOwner(t_pOwner)
{
    //announce
    std::cout << "Ai created for enemy " << pOwner->id << std::endl;
}


