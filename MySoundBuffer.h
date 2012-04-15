#ifndef MYSOUNDBUFFER_H_INCLUDED
#define MYSOUNDBUFFER_H_INCLUDED

#include "DataBank.h"
#include <SFML/System/Resource.hpp>
#include <SFML/Audio/AudioResource.hpp>

//typedef short Int16;

class MySoundBuffer : protected sf::Sound
{
    public:
        std::vector<short> getData();
};

#endif // MYSOUNDBUFFER_H_INCLUDED
