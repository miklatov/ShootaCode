#include <iostream>
#include "GameObject.h"

GameObject::GameObject(DataBank *t_pData) : Entity(t_pData)
{
//    std::cout << "Creating GamObject" << std::endl;

    destroy = false;

    //add self to data bank
    pData->addObject(this);

    //add type
    type+=ClassType::GameObject;

}

void GameObject::changeSprite(std::string imageName)
{
    //see if sprite exists
    GfxBank::iterator iGfx = pData->gfxBank.find(imageName);
    if (iGfx==pData->gfxBank.end())
    {
        std::cout << "Error: Image " << imageName << " not present in gfxBank" << std::endl;
    }
    currentSprite.SetImage(pData->gfxBank[imageName]);

    //update dimensions
    dims = Vector2d(currentSprite.GetSize().x , currentSprite.GetSize().y);

//    std::cout << "DIMS: " << dims << std::endl;

}

void GameObject::update(float elapsed)
{
    //update coords
//    std::cout << coords;
    coords+=velocity*elapsed;
    //ensure all coords match
    currentSprite.SetX(coords.x);
    currentSprite.SetY(coords.y);
}

//void GameObject::addSound(std::string name, std::string dbName, int volume)
//{
//    std::map<std::string,sf::SoundBuffer>::iterator iBuf = pData->sfxBank.find(dbName);
//    if(iBuf==pData->sfxBank.end())
//    {
//        std::cout << "SOUND NOT PRESENT IN DATA BANK" << std::endl;
//        int dump;
//        std::cin >> dump;
//    }
//    sounds[name].SetBuffer(pData->sfxBank[dbName]);
//    sounds[name].SetVolume(volume);
//}

void GameObject::playSound(std::string soundName, int vol)
{
    std::cout << "Playing sound " << pData->currSound << std::endl;
//    if(pData->sounds[pData->currSound]!=NULL)
//    {

//    }

    pData->sounds[pData->currSound] = sf::Sound();
    pData->sounds[pData->currSound].SetBuffer(pData->sfxBank[soundName]);
    pData->sounds[pData->currSound].SetVolume(vol);
    pData->sounds[pData->currSound].Play();

    if(++pData->currSound==pData->maxSounds)
    {
        pData->currSound=0;
    }

//     pData->sounds[pData->currSound]->Stop();
//        delete pData->sounds[pData->currSound];
//    pData->sounds[id].SetBuffer(pData->sfxBank[soundName]);
//    pData->sounds[id].SetVolume(vol);
//    pData->sounds[id].Play();
}
