#include "Player.h"
#include "XpModule.h"

Player::Player(DataBank* t_pData) : Ship(t_pData)
{
    //add type
    type+=ClassType::Player;

    //add XpModule
    pXp = new XpModule(this);
}
