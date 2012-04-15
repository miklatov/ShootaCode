#include "GameWindow.h"
#include "GameState.h"

GameWindow::GameWindow(DataBank* t_pData, Vector2d t_screenDims)
{
    pData = t_pData;
    screenDims = t_screenDims;
    pWindow = new sf::RenderWindow(sf::VideoMode(screenDims.x,screenDims.y,32), "Sonority War");

    //create states
    pPlayState = new PlayGameState(this);
    pPauseState = new PauseGameState(this);
    pCurrentState = pPlayState;
}

void GameWindow::changeState(GameState *pGameState)
{
    pCurrentState->onExit();
    pCurrentState = pGameState;
    pCurrentState->onEnter();
    pCurrentState->onExecute();
}
