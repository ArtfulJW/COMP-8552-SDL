//
// Created by super on 2025-10-02.
//

#ifndef COMP_8552_WEEK1_CLION_COLLISION_H
#define COMP_8552_WEEK1_CLION_COLLISION_H

#include <SDL3/SDL_rect.h>
#include "Component.h"

class Collision
{
public:
    // Axis Aligned Bounding Box
    static bool AABB(const SDL_FRect& rectA, const SDL_FRect& rectB);
    static bool AABB(const Collider& colA, const Collider& colB);
};

#endif //COMP_8552_WEEK1_CLION_COLLISION_H