#pragma once

#include "SDL3/SDL.h"

class Game
{
public:
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
    void Update();

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
    
private:
    int FrameCount = 0;
    bool bIsRunning;

    SDL_Window* SDLWindow;
    SDL_Renderer* SDLRenderer;

    Uint8 r,g,b,a; 
};