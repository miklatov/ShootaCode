#include "Projectile.h"
//#include "Const.h"
#include "Message.h"
#include "GameWindow.h"

Projectile::Projectile(DataBank* t_pData) : GameObject(t_pData)
{
    //add type
    type+=ClassType::Projectile;
};

void Projectile::update(float elapsed)
{
    //update coords
    coords+=velocity*elapsed;
    //ensure all coords match
    currentSprite.SetX(coords.x);
    currentSprite.SetY(coords.y);

    //check bounds
    if (coords.y < 0 || coords.y > pData->pGameWindow->screenDims.y || coords.x < 0 || coords.x > pData->pGameWindow->screenDims.x)
    {
        std::cout << "Marking projectile " << id << " for destruction" << std::endl;
//        destroy = true;
        std::vector<std::string> args;
        args.push_back("die");
        Message* pDieMessage = new Message(id,id,0,args);
        sendMessage(pDieMessage);
    }


}
