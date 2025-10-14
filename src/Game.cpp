#include "Game.h"

// #include "GameObject.h"
#include "AssetManager.h"
#include "Map.h"
#include "iostream"
#include "ostream"

// Map* map = nullptr;
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

    AssetManager::loadAnimation("player", "../asset/animations/bull_animations.xml");

    world.getMap().load("../Asset/map.tmx", TextureManager::Load("../Asset/tileset.png"));
    for (auto& collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto& c = e.addComponent<Collider>("wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        // Have a visual of colliders
        SDL_Texture* tex = TextureManager::Load("../Asset/tileset.png");
        SDL_FRect colSrc {0, 32, 32, 32};
        SDL_FRect colDst {c.rect.x, c.rect.y, c.rect.w, c.rect.h};
        e.addComponent<Sprite>(tex, colSrc, colDst);
    }
    // map = new Map();
    // player = new GameObject("../Asset/ball.png", 0, 0);

    // Add Entities
    for (auto& transform : world.getMap().spawnPoints) {
        auto& item(world.createEntity());
        auto& itemTransform = item.addComponent<Transform>(Vector2D(transform.position.x, transform.position.y), 0.0f, 1.0f);
        SDL_Texture* itemTex = TextureManager::Load("../asset/coin.png");
        SDL_FRect itemSrc {0,0,32,32};
        SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y, 32, 32};
        item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
        auto& itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDest.w;
        itemCollider.rect.h = itemDest.h;
    }

    auto& cam = world.createEntity();
    SDL_FRect camView;
    camView.w = width;
    camView.h = height;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0,0), 0.0f, 1.0f);
    auto& playerVelocity = player.addComponent<Velocity>(Vector2D(0,0), 120.0f);

    Animation anim = AssetManager::getAnimation("player");
    player.addComponent<Animation>(anim);

    // No longer using Mario
    // SDL_Texture* tex = TextureManager::Load("../asset/mario.png");
    // SDL_FRect playerSrc{0,0,32,44};

    SDL_Texture* tex = TextureManager::Load("../asset/animations/bull_anim.png");
    SDL_FRect playerSrc = anim.clips[anim.currentClip].frameIndices[0]; // Get the first frame of the current clip
    SDL_FRect playerDst{playerTransform.position.x,playerTransform.position.y,64,64};
    player.addComponent<Sprite>(tex, playerSrc, playerDst);
    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    // Add player tag
    player.addComponent<PlayerTag>();
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

    world.update(deltaTime, event);
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

    world.render();

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