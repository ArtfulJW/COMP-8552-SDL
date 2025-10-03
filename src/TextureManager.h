//
// Created by User on 9/9/2025.
//

#ifndef COMP_8552_WEEK1_CLION_TEXTUREMANAGER_H
#define COMP_8552_WEEK1_CLION_TEXTUREMANAGER_H

#include "SDL3_image/SDL_image.h"

class TextureManager {
public:
   static SDL_Texture* Load(const char* path);
   static void Draw(SDL_Texture* InTexture, SDL_FRect SourceFRect, SDL_FRect DestFRect);
};

#endif //COMP_8552_WEEK1_CLION_TEXTUREMANAGER_H