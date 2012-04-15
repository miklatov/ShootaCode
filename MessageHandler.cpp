#include "MessageHandler.h"
#include "Message.h"
#include "GameObject.h"
#include "Ship.h"
#include "Projectile.h"
#include "Player.h"
#include "XpModule.h"

MessageHandler::MessageHandler(DataBank* t_pData)
{
    pData = t_pData;
    Message::pHandler = this;
}

void MessageHandler::addMessage(Message* pMessage)
{
    //announce
//    std::cout << "Adding message: Source=" << pMessage->idFrom << "\n"
//              << "                  Dest=" << pMessage->idTo << "\n"
//              << "                 Delay=" << pMessage->delay << "\n"
//              << "                  Args=";
//    for (int a=0; a<pMessage->args.size(); ++a)
//    {
//        std::cout << pMessage->args[a] << ",";
//    }
//    std::cout << "\b)" << std::endl;

//    //if instant, dispatch immediately
//    if(pMessage->delay==Immediate)
//    {
//        execute(pMessage);
//        delete pMessage;
//    }
    //add to queue
//    else
//    {
        messageQueue.push_back(pMessage);
//    }
}

bool compare_messages_in_list(Message* pA, Message *pB)
{
    return (pA->delay < pB->delay);
}

void MessageHandler::updateQueue()
{
    //sort Q
    messageQueue.sort(compare_messages_in_list);
    MessageQueue::iterator iQueue = messageQueue.begin();
    MessageQueue::iterator iQueueE= messageQueue.end();
    while(iQueue!=iQueueE)
    {
        (*iQueue)->delay=(*iQueue)->delay - clock.GetElapsedTime();
//        std::cout << "QD: " << (*iQueue)->delay << std::endl;

        if((*iQueue)->delay <0)
        {
            execute(*iQueue);

            //delete
            delete (*iQueue);
            iQueue=messageQueue.erase(iQueue);
        }
        else
        {
            ++iQueue;
        }
    }
    clock.Reset();
}

bool MessageHandler::execute(Message* pMessage)
{
    //references
    Args &args = pMessage->args;
    EntityId &from = pMessage->idFrom;
    EntityId &to = pMessage->idTo;
    ObjectMap &obj = pData->objectMap;

    GameObject* pFrom = pData->objectMap[from];
    GameObject* pTo = pData->objectMap[to];

    if (pFrom==NULL)
    {
//        std::cout << "From (" << from << ") no longer exists" << std::endl;
//        return false;
    }

    if (pTo==NULL)
    {
//        std::cout << "To (" << to << ") no longer exists" << std::endl;
        return false;
    }

// TODO (shaldenby#1#): perhaps have a map of strings (or better, a vector of enums (e.g. 'die','damage',etc)) of the message type, to allow for very fast look up (O(nlogn) or O(1))

    for (int a=0; a<args.size(); ++a)
    {
        //die
        if (args[a]=="die")
        {
//            delete iObj->second;
//            obj.erase(pMessage->idFrom);
            delete pData->objectMap[to];
            obj.erase(to);


        }
        //damage
        else if (args[a]=="damage")
        {
// TODO (shaldenby#1#): \If you need runtime typing, you can achieve a similar result by adding a classOf() virtual member function to the base class of your hierarchy and overriding that member function in each subclass. If classOf() returns a unique value for each class in the hierarchy, you'll be able to do type comparisons at runtime.
            if(pTo->isType(ClassType::Ship))
            {
                //cast pointer
                Ship* pShip= static_cast<Ship*>(pTo);
                pShip->modifyHealth(-(atoi(args[a+1].c_str())));
            }


//            iObj->second.modifyHealth(atoi(args[a+2].c_str()));
        }
        else if(args[a]=="collide")
        {
            //bullet ->
            if(pFrom->isType(ClassType::Projectile))
            {
                // ->ship?
                if(pTo->isType(ClassType::Ship))
                {
                    Projectile* pProjectile = static_cast<Projectile*>(pFrom);
                    Ship* pShip = static_cast<Ship*>(pTo);
                    //damage
                    ///@MESSAGE
                    //do damage
                    {
                        std::vector<std::string> args;
                        args.push_back("damage");
                        args.push_back("10");
                        Message* pDamageMessage = new Message(from,to,0,args);
                        pFrom->sendMessage(pDamageMessage);
                    }

                    //change to explosion graphic and slow down
                    pFrom->changeSprite("small_explosion");
                    //and die
                    ///@MESSAGE
                    {
                        std::vector<std::string> args;
                        args.push_back("die");
                        Message* pDieMessage = new Message(from,from,0,args);
                        pFrom->sendMessage(pDieMessage);
                    }
                }
            }
        }
        //add xp
        else if(args[a]=="modXP")
        {
            std::cout << "Dispatching modXp message" << std::endl;
//            int dump;
//            std::cin >> dump;
            //dest should be a player
            if(pTo->isType(ClassType::Player))
            {
                Player* pPlayer = static_cast<Player*>(pTo);
                std::cout << "FGZERGZERGZERGZRGGGE" << std::endl;
//                int dump;
//                std::cin >> dump;
                pPlayer->pXp->addXp(atoi(args[a+1].c_str()));
            }
        }
    }

    return true;
}
