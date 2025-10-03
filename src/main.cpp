#include <iostream>
#include "Game.h"

Game* SDLGame = nullptr;

int main()
{

    const int FPS = 60;
    const int DesiredFrameTime = 1000 / FPS; // 16ms per frame

    Uint64 Ticks = SDL_GetTicks();
    float ActualFrameTime = 0.0f;
    float deltaTime = 0.0f;

    SDLGame = new Game();
    SDLGame->init("8552 Week 1", 800, 600, false);

    while (SDLGame->GetIsRunning())
    {
        int currentTicks = SDL_GetTicks();
        deltaTime = (currentTicks - Ticks) / 1000.0f;
        Ticks = currentTicks;

        SDLGame->HandleEvents();
        SDLGame->Update(deltaTime);
        SDLGame->Render();

        ActualFrameTime = (SDL_GetTicks() - Ticks) / 1000.0f;

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