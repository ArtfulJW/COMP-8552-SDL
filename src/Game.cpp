#include "Game.h"

// #include "GameObject.h"
#include "manager/AssetManager.h"
#include "Map.h"
#include "iostream"
#include "ostream"

// Map* map = nullptr;
// GameObject* player = nullptr;

std::function<void(std::string)> Game::onSceneChangeRequest;

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

    // Load Assets (just some animations)
    AssetManager::loadAnimation("player", "../asset/animations/Swordsman_animations.xml");
    AssetManager::loadAnimation("enemy", "../asset/animations/bird_animations.xml");

    // load scene
    sceneManager.loadScene("Level1", "../asset/map.tmx", width, height);
    sceneManager.loadScene("Level2", "../asset/map2.tmx", width, height);

    sceneManager.changeSceneDeferred("Level1");

    // Resolve callback
    onSceneChangeRequest = [this](std::string sceneName) {
        if (sceneManager.currentScene->getName() == "Level2" && sceneName == "Level2") {
            std::cout << "You Win" << std::endl;
            bIsRunning = false;
            return;
        }

        if (sceneName == "gameover") {
            std::cout << "Game Over" << std::endl;
            bIsRunning = false;
            return;
        }

        // the change scene part
        sceneManager.changeSceneDeferred(sceneName);
    };
}

void Game::HandleEvents()
{
    // SDL_Event SDLEvent;

    /*
     * Checks for next event. If one is available, it will dequeue and store it to passed parameter
     */
    SDL_PollEvent(&event);

    switch(event.type)
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

    // DEPRECATED, MOVED WORLD to SCENE.CPP
    // world.update(deltaTime, event);

    sceneManager.update(deltaTime, event);
}

void Game::Render()
{
    r = 100;
    g = 255;
    b = 50;
    a = 255;

    SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255);

    SDL_RenderClear(SDLRenderer);

    // map->DrawMap();
    // player->draw();

    // DEPRECATED, MOVED WORLD TO SCENE
    // world.render();

    sceneManager.render();

    SDL_RenderPresent(SDLRenderer);
}

void Game::Destroy()
{
    TextureManager::clean();
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