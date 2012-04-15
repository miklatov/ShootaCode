#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include "Entity.h"
#include <vector>
#include <string>

#include "MessageHandler.h"

enum {Immediate};
typedef std::vector<std::string> Args;

class Message
{
    public:
        static MessageHandler* pHandler;
        EntityId idFrom;
        EntityId idTo;

//        Entity* pFrom;
//        Entity* pTo;


        double delay;

        Args args;
        //void execute();

        Message(EntityId t_from, EntityId t_to, double t_delay, Args t_args);
      //  void setStaticMessageHandler(MessageHandler* pMh);
};

#endif // MESSAGE_H_INCLUDED
