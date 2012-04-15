#include "Message.h"


MessageHandler* Message::pHandler = NULL;
Message::Message(EntityId t_from, EntityId t_to, double t_delay, Args t_args): idFrom(t_from) , idTo(t_to) , delay(t_delay) , args(t_args)
{
//    std::cout << "Creating message(" << t_from << "," << t_to << "," << delay << ",(";
//    for (int a=0; a<t_args.size(); ++a)
//    {
////        std::cout << t_args[a] << ",";
//    }
//    std::cout << "\b)" << std::endl;

    //add to queue
    pHandler->addMessage(this);
}
