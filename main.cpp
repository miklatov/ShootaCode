#include <iostream>
#include "Vector2d.h"

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "MessageHandler.h"
#include "Message.h"
#include "CollisionSystem.h"
#include "Meter.h"
#include "XpModule.h"
#include "GameWindow.h"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "GameState.h"

#include <SFML/Audio/Sound.hpp>

int main()
{


    //create databank
    DataBank db("dataConfig.txt", Vector2d(1024,768));
    db.pGameWindow->pCurrentState->onEnter();
    while(true)
    {
        db.pGameWindow->pCurrentState->onExecute();
    }

    return 0;
}
