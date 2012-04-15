#include "XpModule.h"
#include <iostream>

#include "Player.h"

XpModule::XpModule(Player* t_pPlayer) : pPlayer(t_pPlayer)
{
    //initialise level boundaries
    xpForLevel.resize(20);
    xpForLevel[1]=100;
    for (int x=2;x<xpForLevel.size();++x)
    {
        xpForLevel[x]=xpForLevel[x-1]*2;
        std::cout << "L:" << x << "\txp:" << xpForLevel[x] << std::endl;
    }

    level = 1;
    xp = 0;
}

void XpModule::addXp(int modXp)
{

    xp+=modXp;

    while (xp>=xpForLevel[level])
    {
        ++level;
        levelUp();
    }
}

void XpModule::levelUp()
{
    pPlayer->playSound("levelup",50);
    std::cout << "LevelUp!!!" << std::endl;
    std::cout << "0: +100 HP" << std::endl;
    std::cout << "1: +100 Speed " << std::endl;
    std::cout << "2: +100 Shot Speed" << std::endl;
    std::cout << "3: -0.04 Shot Cooldown" << std::endl;

    int dump;
    std::cin >> dump;

    switch(dump)
    {
        case 0: //health
            pPlayer->maxHealth+=100;
            break;
        case 1: //speed
            pPlayer->statSpeed+=100;
            break;
        case 2: //shot speed
            pPlayer->statShotSpeed+=100;
            break;
        case 3: //shot cooldown
            pPlayer->statShotCoolDown-=0.04;
            break;

    }

    //boost health
    pPlayer->health = pPlayer->maxHealth;
}

