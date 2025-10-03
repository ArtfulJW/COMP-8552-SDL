//
// Created by User on 9/9/2025.
//

#ifndef COMP_8552_WEEK1_CLION_GAMEOBJECT_H
#define COMP_8552_WEEK1_CLION_GAMEOBJECT_H

#include "Game.h"

class GameObject {
    public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

public:
    void update(float deltaTime);
    void draw();

private:
    float xPos{};
    float yPos{};

    SDL_Texture* texture;
    SDL_FRect srcRect{}, dstRect{};
};

#endif //COMP_8552_WEEK1_CLION_GAMEOBJECT_H