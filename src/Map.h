//
// Created by User on 9/9/2025.
//

#ifndef COMP_8552_WEEK1_CLION_MAP_H
#define COMP_8552_WEEK1_CLION_MAP_H

#include "SDL3/SDL.h"

class Map{

public:
    Map();
    ~Map();

    void LoadMap(int Data[10][15]);
    void DrawMap();

private:
    SDL_FRect src{}, dest{};

    SDL_Texture* Water = nullptr;
    SDL_Texture* Dirt = nullptr;
    SDL_Texture* Grass = nullptr;

    int MapData[10][15]{};
};

#endif //COMP_8552_WEEK1_CLION_MAP_H