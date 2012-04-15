#include "MySoundBuffer.h"

std::vector<short> MySoundBuffer::getData()
{
    return GetBuffer()->mySamples;
}
