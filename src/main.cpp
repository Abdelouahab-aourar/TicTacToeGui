#include "Engine.hpp"
#include "Game/Game.hpp"


#define WIN_WIDTH 320 * 2
#define WIN_HEIGHT 480 * 2

int main(int args, char** argv)
{
    Engine::Get().Init(WIN_WIDTH, WIN_HEIGHT, "TicTacToe");

    Game game;

    while(Engine::Get().isRunning())
    {
        Engine::Get().HandleEvents();

        game.update();

        Engine::Get().ClearScreen(246, 246, 232);

        game.render();

        Engine::Get().Present();
    }

    return 0;
}

