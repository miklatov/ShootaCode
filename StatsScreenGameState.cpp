#include "GameState.h"

StatsScreenGameState::StatsScreenGameState(GameWindow* t_pGameWindow) : GameState(t_pGameWindow)
{

}

void StatsScreenGameState::onEnter()
{
    //announce
    std::cout << "StatsScreenGameState::onEnter()" << std::endl;

}

void StatsScreenGameState::onExecute()
{
    std::cout << "StatsScreenGameState::onExecute()" << std::endl;

      //create pause logo
    sf::String pauseStr;
    pauseStr.SetText("PAUSED");
    pauseStr.SetX(pGameWindow->screenDims.x/2);
    pauseStr.SetY(pGameWindow->screenDims.y/2);

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
                pGameWindow->changeState(pGameWindow->pPlayState);
            }
        }

        // Clear the screen (fill it with black color)
//        pGameWindow->pWindow->Clear();

        pGameWindow->pWindow->Draw(pauseStr);
        pGameWindow->pWindow->Display();

        // Get elapsed time
//        float ElapsedTime = pGameWindow->pWindow->GetFrameTime();

        //EVENTS
//        std::cout << ElapsedTime << std::endl;
//        if (pGameWindow->pWindow->GetInput().IsKeyDown(sf::Key::Left))
//        {
//            std::cout << "UNPAUSING" << std::endl;
//            pGameWindow->changeState(pGameWindow->pPlayState);
//        }
    }

}

void StatsScreenGameState::onExit()
{
    //announce
    std::cout << "StatsScreenGameState::onExit()" << std::endl;
}
