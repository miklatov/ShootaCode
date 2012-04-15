#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "DataBank.h"
#include "Enums.h"

//forward decs
class Message;

typedef unsigned int EntityId;

class Entity
{
    public:
        int type;
        DataBank* pData;
        static EntityId idCounter;
        EntityId id;
        Entity(DataBank* t_pData);
        void sendMessage(Message* pMessage);
        bool isType(int query);
};

#endif // ENTITY_H_INCLUDED
