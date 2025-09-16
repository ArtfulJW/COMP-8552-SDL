#include "Game.h"

// #include "GameObject.h"
#include "Map.h"
#include "iostream"
#include "ostream"

Map* map = nullptr;
// GameObject* player = nullptr;

Game::Game()
{
    
}

Game::~Game()
{
    Destroy();
}

void Game::init(const char* title, int width, int height, bool bIsFullscreen)
{
    int flags = 0;
    if (bIsFullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 1)
    {
        std::cout << "Subsystem Initialized..." << std::endl;
        SDLWindow = SDL_CreateWindow(title, width, height, bIsFullscreen);

        if (SDLWindow)
        {
            std::cout << "Window Created..." << std::endl;
        }

        SDLRenderer = SDL_CreateRenderer(SDLWindow, nullptr);
        if (SDLRenderer)
        {
            std::cout << "Renderer Created..." << std::endl;
        }
        else
        {
            std::cout << "Renderer could not be created..." << std::endl;
            return;
        }

        bIsRunning = true;
    }
    else
    {
        bIsRunning = false;
    }

    map = new Map();
    // player = new GameObject("../Asset/ball.png", 0, 0);

    // Add Entities
    auto& player(world.createEntity());
    auto& playerPosition = player.addComponent<Position>(0,0);

    SDL_Texture* tex = TextureManager::Load("../asset/ball.png");
    SDL_FRect playerSrc{0,0,32,32};
    SDL_FRect playerDst{playerPosition.x,playerPosition.y,64,64};
    player.addComponent<Sprite>(tex, playerSrc, playerDst);
}

void Game::HandleEvents()
{
    SDL_Event SDLEvent;

    /*
     * Checks for next event. If one is available, it will dequeue and store it to passed parameter
     */
    SDL_PollEvent(&SDLEvent);

    switch(SDLEvent.type)
    {
        case SDL_EVENT_QUIT:
            bIsRunning = false;
            break;
        default:
            break;
    }
}

void Game::Update(float deltaTime)
{
    // // FrameCount++;
    // std::cout << FrameCount << std::endl;
    //
    // // Remember to update Player
    // player->update(deltaTime);

    world.update(deltaTime);
}

void Game::Render()
{
    r = 100;
    g = 255;
    b = 50;
    a = 255;

    SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);

    SDL_RenderClear(SDLRenderer);

    map->DrawMap();
    // player->draw();

    world.render();

    SDL_RenderPresent(SDLRenderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();
    std::cout << "Game Destroyed" << std::endl;
}

void Game::randomizeColor() {

    if (FrameCount % 60 == 0) {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        a = rand() % 255;
        SDL_SetRenderDrawColor(SDLRenderer, r, g, b, a);

        SDL_RenderClear(SDLRenderer);
        SDL_RenderPresent(SDLRenderer);
    }

}