//
// Created by User on 9/9/2025.
//

#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include <ostream>

extern Game* SDLGame;
std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;

SDL_Texture *TextureManager::Load(const char *path) {

    // Caching: Storing the result of some work so you don't have to repeat the work next time.
    // Check if the texture already exists in the map
    auto it = textures.find(path);
    if (it != textures.end())
    {
        return it->second;
    }

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

    // Check if the texture creation was successful
    if (!TempTexture)
    {
        std::cout << "Failed to create texture: " << path << std::endl;
        return nullptr;
    }

    // Store the new texture in the cache
    textures[path] = TempTexture;

    return TempTexture;
}

void TextureManager::Draw(SDL_Texture *InTexture, SDL_FRect SourceFRect, SDL_FRect DestFRect) {

    // Draw texture to screen from VRAM.
    SDL_RenderTexture(SDLGame->SDLRenderer, InTexture, &SourceFRect, &DestFRect);
}

void TextureManager::clean()
{
    for (auto& tex : textures)
    {
        SDL_DestroyTexture(tex.second);
        tex.second = nullptr;
    }
    textures.clear();
}
