#include <iostream>
#include "Game.h"

Game* SDLGame = nullptr;

int main()
{

    const int FPS = 60;
    const int DesiredFrameTime = 1000 / FPS; // 16ms per frame

    Uint64 Ticks;
    int ActualFrameTime;

    SDLGame = new Game();
    SDLGame->init("8552 Week 1", 800, 600, false);

    while (SDLGame->GetIsRunning())
    {
        Ticks = SDL_GetTicks();
        SDLGame->HandleEvents();
        SDLGame->Update();
        SDLGame->Render();

        ActualFrameTime = SDL_GetTicks() - Ticks;

        // Frame Limiter
        if (DesiredFrameTime > ActualFrameTime)
        {
            SDL_Delay(DesiredFrameTime - ActualFrameTime);
        }
    }

    delete SDLGame;
    
    std::cout << "Hello World!\n";
    return 0;
}