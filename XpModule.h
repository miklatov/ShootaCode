#ifndef XPMODULE_H_INCLUDED
#define XPMODULE_H_INCLUDED

#include <vector>

//forward dec
class Player;

class XpModule
{
    public:
        Player* pPlayer;
        int level;
        std::vector<int> xpForLevel;
        int xp;

        XpModule(Player* t_pPlayer);
        void addXp(int xpMod);
        void setLevel(int level);
        void levelUp();

};
#endif // XPMODULE_H_INCLUDED
