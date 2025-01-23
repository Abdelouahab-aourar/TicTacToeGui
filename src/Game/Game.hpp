#pragma once

#include "Engine.hpp"

enum State{
    MAINMENU,
    PLAYING,
    WON,
    DRAW
};

enum Cell{
    EMPTY,
    X,
    O
};

class Game
{
public:
    Game();

    void update();
    
    void render();


    ~Game();

private:
    int board[3][3];

    int turnCount;

    SDL_Rect BoardDest;
    SDL_Texture* BoardTex;
    SDL_Texture* X_O_Tex;
    SDL_Texture* Status;

    SDL_Texture* Background;
    SDL_Texture* Title;

    SDL_Texture* Won;
    // SDL_Texture* Draw;

    Cell currentTurn;

private:
    void initMainmenu();
    void updateMainmenu();
    void renderMainmenu();

    void initPlaying();
    void updatePlaying();
    void renderPlaying();

    void initWon();
    void updateWon();
    void renderWon();

    void initDraw();
    void updateDraw();
    void renderDraw();
};

