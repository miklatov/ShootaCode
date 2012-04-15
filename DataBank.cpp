#include "DataBank.h"
#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "CollisionSystem.h"
#include "Collectable.h"
#include "Enemy.h"
#include "Message.h"
#include "GameWindow.h"
#include "Player.h"
#include <sstream>

DataBank::DataBank(std::string dataConfigFile, Vector2d t_screenDims)
{
    //announce
    std::cout << "Loading game data from " << dataConfigFile << std::endl;

    //prepare file
    std::ifstream input;
    input.open(dataConfigFile.c_str());
    if(!input.is_open())
    {
        std::cout << "Failed to open " << dataConfigFile << std::endl;
        exit(EXIT_FAILURE);
    }

    //get args
    std::vector<std::string> args;
    std::string a("");
    while(input >> a)
    {
        args.push_back(a);
    }

    //parse args
    for (int a=0; a<args.size(); ++a)
    {
        //gfx
        if (args[a]=="#GFX")
        {
            int g = a+1;
            while(g < args.size() && args[g][0]!='#')
            {
                //split string
                size_t comma = args[g].find(',');
                std::string gameName, fileName;
                gameName = args[g].substr(0,comma);
                fileName = args[g].substr(comma+1);
                sf::Image tempImage;
                tempImage.LoadFromFile(fileName);
//                std::cout << gameName << "\t" << fileName << std::endl;
                gfxBank.insert(std::pair<std::string, sf::Image>(gameName,tempImage));

                std::cout << "GFX Loaded: " << gfxBank.size() << std::endl;

                ++g;
            }
        }

        //sfx
        if (args[a]=="#SFX")
        {
            int g = a+1;
            while(g < args.size() && args[g][0]!='#')
            {
                //split string
                size_t comma = args[g].find(',');
                std::string gameName, fileName;
                gameName = args[g].substr(0,comma);
                fileName = args[g].substr(comma+1);
                sf::SoundBuffer tempSound;
                tempSound.LoadFromFile(fileName);
//                std::cout << gameName << "\t" << fileName << std::endl;
                sfxBank.insert(std::pair<std::string, sf::SoundBuffer>(gameName,tempSound));

                std::cout << "SFX Loaded: " << sfxBank.size() << std::endl;

                ++g;
            }
        }
    }

    //sort out sound vector
    maxSounds = 200;
    sounds.resize(maxSounds, sf::Sound());
    currSound = 0;

    //create player
    pPlayer = new Player(this);
    //build modules

    std::cout << "Init messagehandler" << std::endl;
    pMessageHandler = new MessageHandler(this);
    std::cout << "Init gamewindow" << std::endl;
    pGameWindow = new GameWindow(this,t_screenDims);
    std::cout << "Init collisionsystem" << std::endl;
    pCollisionSystem = new CollisionSystem(this);
}

void DataBank::addObject(GameObject* pObj)
{
    objectMap.insert(std::pair<EntityId, GameObject*>(pObj->id , pObj));
//    std::cout << "Added GameObject " << pObj->id << " to databank objectMap" << std::endl;
}

void DataBank::updateObjects(float elapsed)
{
    if (objectMap.size()>0)
    {
        ObjectMap::iterator iObj = objectMap.begin();
        while(iObj!=objectMap.end())
        {
            //check it still exists!
            if(iObj->second!=NULL)
            {
                iObj->second->update(elapsed);
            }
            ++iObj;
        }
    }
}

void DataBank::updateCollisionSystem()
{
    pCollisionSystem->updateGrid();
}

void DataBank::detectAllCollisions()
{
    if (objectMap.size()>0)
    {
        ObjectMap::iterator iObj = objectMap.begin();

        while(iObj!=objectMap.end())
        {
// TODO (shaldenby#1#): hmm, this currently passes the entity id to the collision system, which then RE-SEARCHES the objectmap, when infact, it'd be MUCH faster to pass the iterator iObj to the collisiondetection system instead
// TODO (shaldenby#1#): recommended to only detect collisions for objects that are moving

            IdList collisions= pCollisionSystem->detectCollisions(iObj->first);
            if (collisions.size()>0)
            {

                //get pointer to target
                GameObject* victim = objectMap[collisions.front()];
                //if its a bullet colliding with anything
                if (iObj->second->isType(ClassType::Projectile))
                {
                    //as long as it's not a coin or summats
                    if(!victim->isType(ClassType::Collectable) && !victim->isType(ClassType::Projectile))
                    {
                         std::cout << "projectile " << iObj->second->id << " has hit object" << collisions.front() << std::endl;
                        ///@@MESSAGE
                        //collide
                        {
                            ///@SOUNDPLAY
                            iObj->second->playSound("hit",26);
                            std::vector<std::string> args;
                            args.push_back("collide");
                            args.push_back("10");
                            Message* pMessage = new Message(iObj->second->id,collisions.front(),0,args);
                            iObj->second->sendMessage(pMessage);
                        }
                    }

                }
                //or if it's a player hitting something
                else if(iObj->second->isType(ClassType::Player))
                {
                    //collectable?
                    if(victim->isType(ClassType::Collectable))
                    {
                        ///@MESSAGE
                        //die
                        {
                            std::vector<std::string> args;
                            args.push_back("die");
                            Message* pMessage = new Message(iObj->second->id,victim->id,0,args);
                            victim->sendMessage(pMessage);
                        }

                        //give xp to player
                        {
                            std::vector<std::string> args;
                            args.push_back("modXP");
                            std::stringstream ss("");
                            Collectable* pCol = static_cast<Collectable*>(victim);
                            ss << pCol->value;
                            args.push_back(ss.str());
                            Message* pMessage = new Message(victim->id,iObj->second->id,0,args);
                            victim->sendMessage(pMessage);
//                            std::cout << "Sent coin message" << std::endl;
//                            int dump;
//                            std::cin >> dump;

                        }
                    }
                    //with an enemy?
                    else if(victim->isType(ClassType::Enemy))
                    {
                        ///@MESSAGE
                        //die
                        {
                            std::vector<std::string> args;
                            args.push_back("die");
                            Message* pMessage = new Message(iObj->second->id,victim->id,0,args);
                            victim->sendMessage(pMessage);
                        }
                        ///@MESSAGE
                        //damage player
                        {
                            Enemy* pEnemy = static_cast<Enemy*>(victim);
                            std::vector<std::string> args;
                            args.push_back("damage");
                            std::stringstream ss("");
                            ss << int(pEnemy->health/2);
                            args.push_back(ss.str());
                            Message* pMessage = new Message(victim->id,iObj->second->id,0,args);
                            victim->sendMessage(pMessage);
                        }
                    }
                }
//                 std::cout << "Object: " << iObj->first <<  " (total:" << objectMap.size() << ") = " << collisions.size() << std::endl;
            }

            ++iObj;
        }
    }
}


