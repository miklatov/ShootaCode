#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include "GameWindow.h"
#include "Player.h"
#include "pausableclock.hpp"

class GameState
{
    public:
        GameWindow* pGameWindow;

        GameState(GameWindow* t_pGameWindow);
        virtual void onEnter()=0;
        virtual void onExecute()=0;
        virtual void onExit()=0;
};


class PlayGameState : public GameState
{
    public:
        sftools::PausableClock mainClock;
        double elapsed, beginTime, prevTime;
        int timeSlice;
        Player* pPlayer;
        std::vector<double> rawVec;
        int totalBaddies;
        sf::Sound sound;
        sf::String score;
        double runningTot;

        PlayGameState(GameWindow* t_pGameWindow);
        void onEnter();
        void onExecute();
        void onExit();
};

class PauseGameState : public GameState
{
    public:
        PauseGameState(GameWindow* t_pGameWindow);
        void onEnter();
        void onExecute();
        void onExit();
};

class StatsScreenGameState : public GameState
{
    public:
        StatsScreenGameState(GameWindow* t_pGameWindow);
        void onEnter();
        void onExecute();
        void onExit();
};


#endif // GAMESTATE_H_INCLUDED
