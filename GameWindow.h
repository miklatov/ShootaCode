#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Vector2d.h"
#include "Enums.h"
#include "DataBank.h"
//#include "GameState.h"

//forward decs
class GameState;

class GameWindow
{
    public:
        DataBank* pData;
        sf::RenderWindow* pWindow;

        Vector2d screenDims;

        GameWindow(DataBank* t_pData, Vector2d screenDims);

        GameState* pCurrentState;

        void changeState(GameState* gamestate);

        //gamestates
        GameState* pPlayState;
        GameState* pPauseState;

};

#endif // GAMEWINDOW_H_INCLUDED
