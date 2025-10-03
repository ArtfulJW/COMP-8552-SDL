//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_COMPONENT_H
#define COMP_8552_WEEK1_CLION_COMPONENT_H
#include <SDL3/SDL_render.h>
#include <string>
#include "../utils/Vector2D.h"

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
};

// Velocity has a direction and speed
struct Velocity {
    Vector2D direction{};
    float speed{};
};

// struct Position {
//     float x = 0.0f;
//     float y = 0.0f;
// };

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
};

struct Collider
{
    std::string tag;
    SDL_FRect rect{};
};

#endif //COMP_8552_WEEK1_CLION_COMPONENT_H