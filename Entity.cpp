#include "Entity.h"
#include <iostream>

#include "Message.h"

EntityId Entity::idCounter = 0;

class MessageHandler;

Entity::Entity(DataBank* t_pDataBank)
{
    static MessageHandler* pMessageHandler;
//    std::cout << "Creating Entity " << idCounter << std::endl;
    id = idCounter++;

    //set databank
    pData = t_pDataBank;

    //set type
    type=ClassType::Entity;
}

void Entity::sendMessage(Message* pMessage)
{

}

bool Entity::isType(int query)
{
//    std::cout << "CHECKING TYPE: " << query << " & " << type << " = " << (type & query) << std::endl;
    return ((type & query) > 0);
}
