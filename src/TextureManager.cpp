//
// Created by User on 9/9/2025.
//

#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include <ostream>

extern Game* SDLGame;

SDL_Texture *TextureManager::Load(const char *path) {

    /*
     * A Surface represents an image in RAM.
     */
    SDL_Surface* TempSurface = IMG_Load(path);

    if (!TempSurface) {
        std::cout << "Failed to load image: " << path << std::endl;
    }

    /*
     * A Texture represents an Image in VRAM.
     */
    SDL_Texture* TempTexture = SDL_CreateTextureFromSurface(SDLGame->SDLRenderer, TempSurface);

    // Cleanup surface
    SDL_DestroySurface(TempSurface);

    return TempTexture;
}

void TextureManager::Draw(SDL_Texture *InTexture, SDL_FRect SourceFRect, SDL_FRect DestFRect) {

    // Draw texture to screen from VRAM.
    SDL_RenderTexture(SDLGame->SDLRenderer, InTexture, &SourceFRect, &DestFRect);
}
