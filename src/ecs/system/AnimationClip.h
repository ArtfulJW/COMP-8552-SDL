//
// Created by User on 10/14/2025.
//

#ifndef COMP_8552_WEEK1_CLION_ANIMATIONCLIP_H
#define COMP_8552_WEEK1_CLION_ANIMATIONCLIP_H
#include <vector>
#include <SDL3/SDL_rect.h>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndices;
};

#endif //COMP_8552_WEEK1_CLION_ANIMATIONCLIP_H