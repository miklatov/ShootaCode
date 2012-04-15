#include "Enemy.h"
#include "GameObject.h"
#include "Projectile.h"
#include "Message.h"
#include "GameWindow.h"

Enemy::Enemy(DataBank* t_pData) : Ship(t_pData)
{
    //add type
    type+=ClassType::Enemy;
}

void Enemy::update(float elapsed)
{
//    std::cout << "updating enemt "<< id << "\n";

    //update coords
    coords+=velocity*elapsed;

    //ensure all coords match
    currentSprite.SetX(coords.x);
    currentSprite.SetY(coords.y);
    //cooldowns
    if(!shotCooledDown)
    {
        shotCoolDown-=elapsed;

        if(shotCoolDown<=0.0)
        {
            shotCooledDown = true;
            shotCoolDown=0.0;
        }
    }

    //shoot
    if(shotCooledDown && rand()%70==0)
    {
        for (int b=0; b<1; ++b)
        {
            GameObject* pBullet = new Projectile(pData);

            pBullet->coords = Vector2d(coords);
            pBullet->changeSprite("weak_bullet");
            pBullet->coords.x+=(dims.x/2);
            pBullet->coords.x-=(pBullet->dims.x/2);
            pBullet->coords.x+=(b*5);
            pBullet->coords.y+=(dims.y + 10);
            pBullet->velocity = Vector2d(velocity.x,statShotSpeed);
            playSound("shoot",13);
        }
        shotCooledDown =false;
        shotCoolDown = statShotCoolDown;
        std::cout << "ShotCoolDown=" << shotCoolDown;
//        int dump;
//        std::cin >> dump;
    }

        //check bounds
    if (coords.y < 0 || coords.y > pData->pGameWindow->screenDims.y || coords.x < 0 || coords.x > pData->pGameWindow->screenDims.x)
    {
//        std::cout << "Marking projectile " << id << " for destruction" << std::endl;
//        destroy = true;
        std::vector<std::string> args;
        args.push_back("die");
        Message* pDieMessage = new Message(id,id,0,args);
        sendMessage(pDieMessage);
    }



}
