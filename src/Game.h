#pragma once

#include "SDL3/SDL.h"

class Game
{
public:

    SDL_Renderer* SDLRenderer = nullptr;

    Game();

    ~Game();

    void init(const char* title, int width, int height, bool bIsFullscreen);

    /*
     * Game Loop Functions
     * Checks for Input and System Events and adds them to a queue.
     */
    void HandleEvents();

    /*
     * Handles Game Logic and changes to game state.
     */
    void Update(float deltaTime);

    /*
     * Handles the drawing the game state to the screen.
     */
    void Render();

    /*
     * Used to free resources
     */
    void Destroy();

    bool GetIsRunning()
    {
        return bIsRunning;
    }

    void randomizeColor();
    
private:
    int FrameCount = 0;
    bool bIsRunning = false;

    SDL_Window* SDLWindow = nullptr;

    Uint8 r,g,b,a; 
};