//
// Created by User on 9/9/2025.
//

#ifndef COMP_8552_WEEK1_CLION_TEXTUREMANAGER_H
#define COMP_8552_WEEK1_CLION_TEXTUREMANAGER_H

#include <string>
#include <unordered_map>

#include "SDL3_image/SDL_image.h"

class TextureManager {
   static std::unordered_map<std::string, SDL_Texture*> textures;
public:
   static SDL_Texture* Load(const char* path);

   static void Draw(SDL_Texture* InTexture, SDL_FRect SourceFRect, SDL_FRect DestFRect);

   static void clean();
};

#endif //COMP_8552_WEEK1_CLION_TEXTUREMANAGER_H