#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Entity.h"
#include "Vector2d.h"
#include <map>
#include <string>
#include <list>
#include <SFML/Audio.hpp>

typedef std::map<std::string,sf::Sound> SoundMap;

class GameObject : public Entity
{
    public:
        GameObject(DataBank* pData);

        sf::Sprite currentSprite;
        SoundMap sounds;
        Vector2d dims;
        Vector2d coords;
        Vector2d facingCoords;
        Vector2d velocity;
        bool destroy;
        //functions
        void changeSprite(std::string imageName);
//        void addSound(std::string name, std::string dbName, int volume);
        void playSound(std::string soundName, int vol);

        virtual void update(float elapsed);


};

#endif // GAMEOBJECT_H_INCLUDED
