//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_COMPONENT_H
#define COMP_8552_WEEK1_CLION_COMPONENT_H
#include <SDL3/SDL_render.h>

struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
};

#endif //COMP_8552_WEEK1_CLION_COMPONENT_H