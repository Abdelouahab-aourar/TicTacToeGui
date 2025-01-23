#include "Game.hpp"

#define BOARD_X 50
#define BOARD_Y 210
#define BOARD_W 270*2
#define BOARD_H 270*2

State state;

Game::Game()
{

    BoardTex = Engine::Get().loadTexture("res/Board.png");
    X_O_Tex = Engine::Get().loadTexture("res/X_O.png");
    Status = Engine::Get().loadTexture("res/Status.png");

    Background = Engine::Get().loadTexture("res/Background.png");
    Title = Engine::Get().loadTexture("res/Title.png");

    Won = Engine::Get().loadTexture("res/Won.png");
    // Draw = Engine::Get().loadTexture("res/Draw.png");

    state = MAINMENU;
    initMainmenu();

    BoardDest = {BOARD_X, BOARD_Y, BOARD_W, BOARD_H};

}

void Game::update()
{
    switch(state)
    {
        case PLAYING:
            updatePlaying();
            break;
        case MAINMENU:
            updateMainmenu();
            break;
        case WON:
            updateWon();
            break;
        case DRAW:
            updateDraw();
            break;
        default:
            break;
    }
}
    
void Game::render()
{
    switch(state)
    {
        case PLAYING:
            renderPlaying();
            break;
        case MAINMENU:
            renderMainmenu();
            break;
        case WON:
            renderWon();
            break;
        case DRAW:
            renderDraw();
            break;
        default:
            break;
    }
}

Game::~Game()
{

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////PRIVATE//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Rect titleDest = {
        320-295,
        100,
        590,
        130
};

SDL_Rect player1_SRC = {
    0,
    32,
    195,
    28
};

SDL_Rect player2_SRC = {
    202,
    32,
    195,
    28
};


SDL_Rect player1_DEST = {
    30,
    880,
    195,
    28
};


SDL_Rect player2_DEST = {
    30,
    920,
    195,
    28

};

void Game::initPlaying()
{
    memset(board, 0, sizeof(board));
    currentTurn = X;
    turnCount = 0;    
}

bool checkWin(int board[][3], Cell currentTurn) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentTurn && board[i][1] == currentTurn && board[i][2] == currentTurn) {
            return true;
        }
        if (board[0][i] == currentTurn && board[1][i] == currentTurn && board[2][i] == currentTurn) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == currentTurn && board[1][1] == currentTurn && board[2][2] == currentTurn) {
        return true;
    }
    if (board[0][2] == currentTurn && board[1][1] == currentTurn && board[2][0] == currentTurn) {
        return true;
    }

    return false;
}

void Game::updatePlaying()
{
    if(Engine::Get().getMouseState().LMBreleased)
    {
        int j = (Engine::Get().getMouseState().x - BOARD_X) / (BOARD_H/3);
        int i = (Engine::Get().getMouseState().y - BOARD_Y) / (BOARD_W/3);

        if(i >= 0 && j >= 0 && i <= 2 && j <= 2 && board[i][j] == EMPTY)
        {
            board[i][j] = currentTurn;
            currentTurn = (currentTurn == X)? O : X;
            turnCount++;
        }
    }

    if(checkWin(board, (currentTurn == X)? O : X))
    {
        state = WON;
        initWon();
    } else if(turnCount == 9){
        state = DRAW;
        initDraw();
    }

    if(currentTurn == X)
    {
        player1_SRC.y = 0;
        player2_SRC.y = 32;
    }else{
        player1_SRC.y = 32;
        player2_SRC.y = 0;
    }

}

void Game::renderPlaying()
{
    Engine::Get().Draw(BoardTex, NULL, &BoardDest);

    Engine::Get().Draw(Status, &player1_SRC, &player1_DEST);
    Engine::Get().Draw(Status, &player2_SRC, &player2_DEST);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != EMPTY)
            {
                SDL_Rect src;
                SDL_Rect dest;

                if(board[i][j] == X)
                {
                    src = {
                        0,
                        0,
                        153,
                        141
                    };
                    dest = {
                        j*154 + BOARD_X + 35 + j*15,
                        i*141 + BOARD_Y + 35 + i*25,
                        153,
                        141
                    };

                }else{
                    src = {
                        155,
                        0,
                        153,
                        141
                    };
                    dest = {
                        j*154 + BOARD_X + 20 + j*15,
                        i*141 + BOARD_Y + 30 + i*25,
                        153,
                        141
                    };

                }
                Engine::Get().Draw(X_O_Tex, &src, &dest);
            }
        }
    }
}

Button* Play;
Button* gitHub1;
Button* gitHub2;

void Game::initMainmenu()
{
    Play = new Button("res/Play.png", 320 - 92, 480, 184, 97, [](){});
    Play->changeTexCoord(0, 0, 184, 97);

    gitHub1 = new Button("res/githubs.png", 20, 960 - 60, 318, 25, [](){});
    gitHub1->changeTexCoord(0, 0, 318, 25);

    gitHub2 = new Button("res/githubs.png", 20, 960 - 30, 318, 25, [](){});
    gitHub2->changeTexCoord(0, 35, 318, 25);

}

void Game::updateMainmenu()
{
    Play->update(0.f);
    if(Play->mouseOver())
        Play->changeTexCoord(0, 97, 184, 97);
    else
        Play->changeTexCoord(0, 0, 184, 97);

    if(Play->clicked())
    {
        state = PLAYING;
        initPlaying();
    }

    gitHub1->update(0.f);
    if(gitHub1->mouseOver())
        gitHub1->changeTexCoord(0, 70, 318, 25);
    else
        gitHub1->changeTexCoord(0, 0, 318, 25);

    if(gitHub1->clicked())
    {
        openWebLink("https://github.com/arialCoding");
    }

    gitHub2->update(0.f);
    if(gitHub2->mouseOver())
        gitHub2->changeTexCoord(0, 105, 318, 25);
    else
        gitHub2->changeTexCoord(0, 35, 318, 25);

    if(gitHub2->clicked())
    {
        openWebLink("https://github.com/Abdelouahab-aourar");
    }

}

void Game::renderMainmenu()
{   
    Engine::Get().Draw(Background, NULL, NULL);
    Engine::Get().Draw(Title, NULL, &titleDest);
    Play->draw();
    gitHub1->draw();
    gitHub2->draw();
}

Button* Replay;

SDL_Rect WonSRC;
SDL_Rect WonDEST;

void Game::initWon()
{
    Replay = new Button("res/Replay.png", 320 - 92, 640, 184, 97, [](){});

    Replay->changeTexCoord(0, 0, 184, 97);

    WonSRC = {
        0,
        (currentTurn == O)? 0 : 515/2,
        440,
        515/2
    };

    WonDEST = {
        320 - 440/2,
        530 - 515/2,
        440,
        515/2
    };
}

void Game::updateWon()
{
    Replay->update(0.f);
    if(Replay->mouseOver())
        Replay->changeTexCoord(0, 97, 184, 97);
    else
        Replay->changeTexCoord(0, 0, 184, 97);
    
    if(Replay->clicked())
    {
        state = PLAYING;
        initPlaying();
    }
}

void Game::renderWon()
{    
    Engine::Get().Draw(Title, NULL, &titleDest);
    Engine::Get().Draw(Won, &WonSRC, &WonDEST);
    Replay->draw();
}

SDL_Rect DrawSRC;
SDL_Rect DrawDest;

void Game::initDraw()
{
    Replay = new Button("res/Replay.png", 320 - 92, 640, 184, 97, [](){});

    Replay->changeTexCoord(0, 0, 184, 97);

    DrawSRC = {
        0,
        520,
        440,
        135
    };

    DrawDest = {
        320 - 440/2,
        530 - 150,
        440,
        135
    };
}

void Game::updateDraw()
{
    Replay->update(0.f);
    if(Replay->mouseOver())
        Replay->changeTexCoord(0, 97, 184, 97);
    else
        Replay->changeTexCoord(0, 0, 184, 97);
    
    if(Replay->clicked())
    {
        state = PLAYING;
        initPlaying();
    }
}

void Game::renderDraw()
{
    
    Engine::Get().Draw(Title, NULL, &titleDest);
    Engine::Get().Draw(Won, &DrawSRC, &DrawDest);
    Replay->draw();
}
