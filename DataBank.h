#ifndef DATABANK_H_INCLUDED
#define DATABANK_H_INCLUDED

#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Vector2d.h"
#include <list>

//forward decs
class GameObject;
class CollisionSystem;
class Meter;
class Player;
class GameWindow;
class MessageHandler;

//typedefs
typedef std::map<std::string, sf::Image> GfxBank;
typedef std::map<std::string, sf::SoundBuffer> SfxBank;
typedef std::map<std::string, sf::Sprite> SpriteGroup;
typedef std::map<std::string, SpriteGroup> SpriteGroupMap;
typedef std::map<long,GameObject*> ObjectMap;
typedef std::map<long,Meter*> MeterMap;
typedef std::list<Meter*> MeterList;

class DataBank
{
    public:
        GfxBank gfxBank;
        SfxBank sfxBank;
        std::vector<sf::Sound> sounds;
        int maxSounds;
        int currSound;
        ObjectMap objectMap;
        MeterList meterList;
        Player* pPlayer;
//        Vector2d screenDimensions;
        CollisionSystem* pCollisionSystem;
        GameWindow* pGameWindow;
        MessageHandler* pMessageHandler;
//        std::map<unsigned int,sf::Sound> sounds;

        void addObject(GameObject* pObj);
        void addMeter(Meter* meter);
        void updateObjects(float elapsed);
        void updateCollisionSystem();
        void detectAllCollisions();
        //constructor
        DataBank(std::string dataConfigFile, Vector2d t_screenDims);
};

#endif // DATABANK_H_INCLUDED
