#include "GameWindow.h"
#include <iostream>
#include "GameState.h"
#include "Player.h"
#include "Projectile.h"
#include "XpModule.h"
#include "Enemy.h"
#include <sstream>
#include "Meter.h"
#include "MessageHandler.h"
#include <fstream>


PlayGameState::PlayGameState(GameWindow* t_pGameWindow) : GameState(t_pGameWindow)
{
//    pGameWindow = t_pGameWindow;
     std::vector<short> myBuffer;
    int steps =pGameWindow->pData->sfxBank["test"].GetSamplesCount();
    std::cout << "STEPS: " << steps << std::endl;
    std::copy(pGameWindow->pData->sfxBank["test"].GetSamples(), pGameWindow->pData->sfxBank["test"].GetSamples()+steps, std::back_inserter(myBuffer));
//    std::vector<short> myBuffer = pGameWindow->pData->sfxBank["test"].GetSamples();


//     	Sound (const SounpGameWindow->pDatauffer &Buffer, bool Loop=false, float Pitch=1.f, float Volume=100.f, const Vector3f &Position=Vector3f(0, 0, 0))
//    ///AUDIO TEST
    std::cout << "BufferSize: " << myBuffer.size() << std::endl;
    int duration = pGameWindow->pData->sfxBank["test"].GetDuration();
    std::cout << "duration  : " << pGameWindow->pData->sfxBank["test"].GetDuration() << std::endl;
    std::cout << "samples per second = " << myBuffer.size() / pGameWindow->pData->sfxBank["test"].GetDuration() << std::endl;
//    int dump;
//    std::cin >> dump;

    std::ofstream outSound;
    outSound.open("sound.txt");
    //int winLen = 44100;
    int winLen = 44100;
    int stepSize = 4410;

    for (int x=0;x<myBuffer.size()-winLen; x+=stepSize)

    //10th of a second
    {

     double totalSq=0;
        for (int y=x; y< x+winLen; ++y)
        {

//        std::cout << myBuffer[x] << "\t";
         //total += myBuffer[y];
         totalSq+= myBuffer[y]/10*myBuffer[y]/10;


        }
//         std::cout << "TotalSq: " << totalSq << std::endl;
        double meanSq = double(totalSq)/(double(myBuffer.size()));
     //   std::cout << "MeanSq : " << int(meanSq) << std::endl;
        double rmsq = sqrt(meanSq);
        rawVec.push_back(rmsq);
       // std::cout << "RMS    : " << int(rmsq) << std::endl;

       outSound << float(x)/44100.f << "\t" << rmsq << std::endl;

    }

    //calculate total
    long total = 0;
    std::vector<double>::iterator iChunk = rawVec.begin();

    while(iChunk!=rawVec.end())
    {
        std::cout << *iChunk << "\t";
        *iChunk= pow(*iChunk,2);

        std::cout << *iChunk << "\n";
                ++iChunk;
    }

    iChunk=rawVec.begin();
    while(iChunk!=rawVec.end())
    {
        total+=*iChunk++;
//        std::cout << total << ",";

    }

    //convert raw to proportion
    iChunk = rawVec.begin();

    float baddies = 3*duration;
    int c=0;
    while(iChunk!=rawVec.end())
    {
        *iChunk=*iChunk/(total/baddies);
//        *iChunk*;
        std::cout << c++ << ": " << *iChunk << std::endl;
        ++iChunk;
    }


    runningTot=0.0;
    outSound.close();

    //start music playing, and start clock()

    sound.SetBuffer(pGameWindow->pData->sfxBank["test"]);
    sound.SetVolume(100);
//    sound.Play();


    ///END AUDIO TEST
//    CollisionSystem cs(&pGameWindow->pData);
//    pGameWindow->pData->pCollisionSystem = &cs;


//    MessageHandler mh;
//    mh.pData = &pGameWindow->pData;
//    Args a;
//    Message::pHandler = dmh;
//    std::cout << Message::pHandler << std::endl;
//    pGameWindow->pData->screenDimensions = Vector2d(1024,768);

//    cs.sectorSize = Vector2d(1024/10,768/10);
//    cs.buildGrid();
    //entity test

    //start game
        //prepare sfml
//    sf::RenderWindow win(sf::VideoMode(pGameWindow->pData->screenDimensions.x,pGameWindow->pData->screenDimensions.y,32), "SFML Graphics");


    std::cout << "Game system initialised" << std::endl;

//    std::list<GameObject*> objects;

    std::cout << "creating player" <<std::endl;
    //create player
    pPlayer = pGameWindow->pData->pPlayer;
    pPlayer->changeSprite("spaceship");
    pPlayer->statShotCoolDown = 0.2 ;
    pPlayer->statShotSpeed = 400;
    pPlayer->statSpeed = 200.0;
    pPlayer->health = 150;
    pPlayer->maxHealth = 150;


//    pGameWindow->pData->pPlayer = &player;

    //create meter
    std::cout << "creating meter" << std::endl;
    Meter m(pPlayer);
    m.dims = Vector2d(pGameWindow->pData->pGameWindow->screenDims.x/10,5);
    m.coords = Vector2d(pGameWindow->pData->pGameWindow->screenDims.x/40 , pGameWindow->pData->pGameWindow->screenDims.y/40);
    m.anchored = true;
    pGameWindow->pData->meterList.push_back(&m);
    std::cout << "done" << std::endl;

    //prepare text variables
    std::cout << "Preparing text variable" << std::endl;
    std::cout << "Creating score string" << std::endl;

    std::cout << "setting font" << std::endl;
    score.SetFont(sf::Font::GetDefaultFont());
    std::cout << "setting text" << std::endl;
//    score.SetText("Hello");
    std::cout << "setting size" << std::endl;
    score.SetSize(50);

    std::cout<<"done" << std::endl;


    pGameWindow->pWindow->SetFramerateLimit(60);
    totalBaddies=0;
    timeSlice=0;

//    int dump;
//    std::cin >> dump;
    std::cout << "Entering outer gameLoop" << std::endl;
    elapsed =0;



    beginTime = mainClock.GetElapsedTime();
    prevTime = mainClock.GetElapsedTime();
}

void PlayGameState::onEnter()
{
    std::cout << "PlayGameState::onEnter()" << std::endl;
        sound.Play();
        mainClock.Start();
}

void PlayGameState::onExecute()
{

    std::cout << "PlayGameState::onExecute()" << std::endl;
     while (pGameWindow->pWindow->IsOpened())
    {
        // Process events
        sf::Event Event;
        while (pGameWindow->pWindow->GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                pGameWindow->pWindow->Close();

            if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::P)
            {
                pGameWindow->changeState(pGameWindow->pPauseState);
            }
        }

        // Clear the screen (fill it with black color)
        pGameWindow->pWindow->Clear();



        // Get elapsed time
        float ElapsedTime = pGameWindow->pWindow->GetFrameTime();

        //EVENTS
        std::cout << ElapsedTime << std::endl;
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::Left))  pGameWindow->pData->pPlayer->coords+=(Vector2d(-(pGameWindow->pData->pPlayer->statSpeed) * ElapsedTime, 0));
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::Right)) pGameWindow->pData->pPlayer->coords+=(Vector2d( (pGameWindow->pData->pPlayer->statSpeed) * ElapsedTime, 0));
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::Up))    pGameWindow->pData->pPlayer->coords+=(Vector2d(0, -(pGameWindow->pData->pPlayer->statSpeed) * ElapsedTime));
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::Down))  pGameWindow->pData->pPlayer->coords+=(Vector2d(0,  (pGameWindow->pData->pPlayer->statSpeed) * ElapsedTime));

        //tests
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::A))
        {
            pGameWindow->pData->pPlayer->statShotCoolDown+=0.001;
            std::cout << "Shot cooldown: " << pGameWindow->pData->pPlayer->statShotCoolDown << "\n";
        }
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::Z))
        {
            pGameWindow->pData->pPlayer->statShotCoolDown-=0.001;
            std::cout << "Shot cooldown: " << pGameWindow->pData->pPlayer->statShotCoolDown << "\n";
        }
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::S))
        {
            pGameWindow->pData->pPlayer->statShotSpeed+=1;
            std::cout << "Bullet Speed: " << pGameWindow->pData->pPlayer->statShotSpeed << "\n";
        }
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::X))
        {
            pGameWindow->pData->pPlayer->statShotSpeed-=1;
            std::cout << "Bullet Speed: " << pGameWindow->pData->pPlayer->statShotSpeed << "\n";
        }
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::D))
        {
            pGameWindow->pData->pPlayer->statSpeed+=1;
            std::cout << "Speed: " << pGameWindow->pData->pPlayer->statSpeed << "\n";
        }
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::C))
        {
            pGameWindow->pData->pPlayer->statSpeed-=1;
            std::cout << "Speed: " << pGameWindow->pData->pPlayer->statSpeed << "\n";
        }
//        if(pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::P))
//        {
//            if(pGameWindow->pWindow->)
//            pGameWindow->changeState(pGameWindow->pPauseState);
//        }

//        if(pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::LShift))
//        {
//            if (m.anchored == false)
//            {
//                m.anchored = true;
//            }
//        }
//        else
//        {
//            m.anchored = false;
//        }
        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::Space) && pGameWindow->pData->pPlayer->shotCooledDown)
        {
            for (int b=0; b<1; ++b)
            {
                GameObject* pBullet = new Projectile(pGameWindow->pData);

                pBullet->coords = Vector2d(pGameWindow->pData->pPlayer->coords);
                pBullet->changeSprite("weak_bullet");
                pBullet->coords.x+=(pGameWindow->pData->pPlayer->dims.x/2);
                pBullet->coords.x-=(pBullet->dims.x/2);
                pBullet->coords.x+=(b*5);
                pBullet->coords.y-=(10);
                pBullet->velocity = Vector2d(b*5,-pGameWindow->pData->pPlayer->statShotSpeed);
//                pGameWindow->pData->pPlayer->sounds["shoot"].Play();
                ///@SOUNDPLAY
                pGameWindow->pData->pPlayer->playSound("shoot",13);
            }

//            Args a;
//            pBullet->sendMessage(new Message(1,2,3.0,a));
            //mh.addMessage(new Message(1,2,3.0,a));
            pGameWindow->pData->pPlayer->startShotCoolDown();
        }

        pGameWindow->pData->updateCollisionSystem();
        pGameWindow->pData->detectAllCollisions();
        pGameWindow->pData->updateObjects(ElapsedTime);



        ///TEST BADDIES


       double currTime = mainClock.GetElapsedTime();
       std::cout << "GetElapsed: " << mainClock.GetElapsedTime() << std::endl;
       std::cout << "currTime: " << currTime << "\tprevTime: " << prevTime << std::endl;
//        unsigned int prevTime = currTime;
        elapsed+= currTime - prevTime;
//        prevTime = currTime;
        std::cout << "elapsed: " << elapsed<<"\n";
        while(elapsed>0.05)
        {

            ++timeSlice;
            std::cout << mainClock.GetElapsedTime()-beginTime << ":\t" << timeSlice << "\t" <<  rawVec[timeSlice] << "\n";
            runningTot+=rawVec[timeSlice];
            while(runningTot>1.0)
            {
                ++totalBaddies;
                Enemy* p = new Enemy(pGameWindow->pData);
                GameObject* pAst =  p;
                int xCo = rand()%int(pGameWindow->pData->pGameWindow->screenDims.x-100) + 50;
                pAst->coords = Vector2d(xCo, 70);
                pAst->changeSprite("enemy_ship01");
                p->maxHealth=20;
                p->health = 20;
                p->statSpeed = rawVec[timeSlice]*1000;
                p->statShotCoolDown=float(rand())/RAND_MAX + 0.3;
                p->statShotSpeed = float(p->statSpeed+200);
//                p->addSound("shoot","explosion",25);
//                p->addSound("death","explosion",100);


                //create a meter
                //create meter
//                Meter* pMeter =new Meter(p);
//                pMeter->dims = Vector2d(pGameWindow->pData->screenDimensions.x/10,5);
//                pMeter->coords = Vector2d(pGameWindow->pData->screenDimensions.x/40 , pGameWindow->pData->screenDimensions.y/40);
//                pMeter->anchored =true;
//                pGameWindow->pData->meterList.push_back(pMeter);
//                std::cout << "done" << std::endl;

//                pAst->velocity = Vector2d(rand()%100 -50,rand()%500 + 100);
                pAst->velocity = Vector2d(rand()%200 -100,p->statSpeed);
                runningTot-=1.0;

            }

            ObjectMap::iterator iEnemy = pGameWindow->pData->objectMap.begin();
            while(iEnemy!=pGameWindow->pData->objectMap.end())
            {
                if(iEnemy->second!=NULL)
                {
                     if(iEnemy->second->isType(ClassType::Enemy))
                     {
                         iEnemy->second->velocity.y = rawVec[timeSlice]*1000;
                     }
                }
                ++iEnemy;
            }

            elapsed-=0.05;
            prevTime+=0.05;
            std::cout << "AFTER DEDUCTION, ELAPSED: " << elapsed << std::endl;
//            int dump;
//            std::cin >> dump;
        }
//        std::cout << "Enemy creation phase complete: Returning to loop" << std::endl;
//        std::cout << "GAMETIME: " << clock() - originalTime << "\n";

        ///END TEST BADDIES

        //DRAW

        //score
        std::stringstream ss("");
        ss << "LVL: " << pGameWindow->pData->pPlayer->pXp->level << "   " << pGameWindow->pData->pPlayer->pXp->xp << " / " << pGameWindow->pData->pPlayer->pXp->xpForLevel[pGameWindow->pData->pPlayer->pXp->level];
        score.SetText(ss.str());
//        int prop = (float(totalBaddies)/float(baddies)) * 100;
//        ss << prop  << "%";
//        score.SetText(ss.str());
        pGameWindow->pWindow->Draw(score);
        ObjectMap::iterator iObj=pGameWindow->pData->objectMap.begin();
        std::cout << "objectSize: " << pGameWindow->pData->objectMap.size() << std::endl;
        while(iObj!=pGameWindow->pData->objectMap.end())
        {
            //check for existence!
            if(iObj->second!=NULL)
            {
                 pGameWindow->pWindow->Draw(iObj->second->currentSprite);
            }

            ++iObj;
        }

        //Draw Meters
//        MeterList::iterator iMeter=pGameWindow->pData->meterList.begin();
//        while(iMeter!=pGameWindow->pData->meterList.end())
//        {
//            if((*iMeter)->update(*pGameWindow->pWindow))
//            {
//                //returns true if meter's target still exists
//                ++iMeter;
//            }
//            else
//            {
//// TODO (shaldenby#1#): This needs reverting. Only like this for debugging, as player is NOT in databank, in objectmap
//
//                //++iMeter;
//                iMeter = pGameWindow->pData->meterList.erase(iMeter);
//            }
//        }
     //   win.Draw(pGameWindow->pData->pPlayer->currentSprite);
//        // Move the sprite
//        if (win.GetInput().IsKeyDown(sf::Key::Left))  objects.front()->currentSprite.Move(-200 * ElapsedTime, 0);
//        if (win.GetInput().IsKeyDown(sf::Key::Right)) objects.front()->currentSprite.Move( 200 * ElapsedTime, 0);
//        if (win.GetInput().IsKeyDown(sf::Key::Up))    objects.front()->currentSprite.Move(0, -200 * ElapsedTime);
//        if (win.GetInput().IsKeyDown(sf::Key::Down))  objects.front()->currentSprite.Move(0,  200 * ElapsedTime);
//
//        // Rotate the sprite
//        if (win.GetInput().IsKeyDown(sf::Key::A))      objects.front()->currentSprite.Rotate(-100 * ElapsedTime);
//        if (win.GetInput().IsKeyDown(sf::Key::S)) objects.front()->currentSprite.Rotate( 100 * ElapsedTime);
//
//        // Display window contents on screen

        pGameWindow->pData->pMessageHandler->updateQueue();
        pGameWindow->pWindow->Display();
//        int dump;
//        std::cin >> dump;

    }


}

void PlayGameState::onExit()
{
    std::cout << "PlayGameState::onExit()" << std::endl;
    sound.Pause();
    mainClock.Pause();
}
