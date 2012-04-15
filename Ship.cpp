#include "Ship.h"
#include "Message.h"
#include "Player.h"
#include "Collectable.h"
#include "XpModule.h"

Ship::Ship(DataBank* t_pData) : GameObject(t_pData)
{
    shotCooledDown = true;
    shotCoolDown = 0.0;

    //add type
    type+=ClassType::Ship;


}

void Ship::update(float elapsed)
{
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
}

void Ship::startShotCoolDown()
{
    shotCooledDown = false;
    shotCoolDown = statShotCoolDown;
}

void Ship::modifyHealth(int mod)
{

    int healthBefore = health;
    health+=mod;

    if (health > maxHealth)
    {
        health = maxHealth;
    }

    if (healthBefore > 0 && health < 1)
    {
        //play death sound
//        sf::Sound death;
//        death.SetBuffer(pData->sfxBank["explosion"]);
//        death.SetVolume(100);
//        death.Play();
        ///@SOUNDPLAY
        playSound("explosion",25);
        //check for death


        ///@MESSAGE
        //die
        {
            std::vector<std::string> args;
            args.push_back("die");
            Message* pDamageMessage = new Message(id,id,0,args);
            sendMessage(pDamageMessage);



//            //ADD XP
//            pData->pPlayer->xp+=10;

            //drop a token
            Collectable* pCoin = new Collectable(pData);

            pCoin->coords = Vector2d(coords);
            pCoin->changeSprite("coin");
            pCoin->velocity = Vector2d(0,75);
            pCoin->value = rand()%50 + 1;

        }
    }
    std::cout << "HP: " << health << " / " << maxHealth << std::endl;
}
