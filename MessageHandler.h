#ifndef MESSAGEHANDLER_H_INCLUDED
#define MESSAGEHANDLER_H_INCLUDED
#include <SFML/Window.hpp>

#include <list>
#include "DataBank.h"


//forward decs
class Message;

typedef std::list<Message*> MessageQueue;



class MessageHandler
{
    public:
        DataBank* pData;
        sf::Clock clock;

        MessageQueue messageQueue;
        void addMessage(Message* pMessage);
        void updateQueue();
        bool execute(Message* pMessage);

        MessageHandler(DataBank* p_data);
};
#endif // MESSAGEHANDLER_H_INCLUDED
