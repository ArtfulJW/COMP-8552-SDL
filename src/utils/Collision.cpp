//
// Created by super on 2025-10-02.
//

#include "Collision.h"


bool Collision::AABB(const SDL_FRect& rectA, const SDL_FRect& rectB)
{
    // Is the right edge of rectA >= to the left edge of rectB
    // Is the right edge of rectB >= to the left edge of rectA
    // Is the bottom edge of rectA >= to the top edge of rectB
    // Is the bottom edge of rectB >= to the top edge of rectA

    if (
        rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y)
    {
        return true;
    }
    return false;

}

bool Collision::AABB(const Collider& colA, const Collider& colB)
{
    if (AABB(colA.rect, colB.rect))
    {
        return true;
    }
    return false;
}