//
// Created by User on 9/9/2025.
//

#ifndef COMP_8552_WEEK1_CLION_MAP_H
#define COMP_8552_WEEK1_CLION_MAP_H

#include <vector>
#include "SDL3/SDL.h"
#include "Component.h"

class Map{

public:
    Map() = default;
    ~Map() = default;

    void load(const char* path, SDL_Texture* ts);
    void draw();

    SDL_Texture* tileset = nullptr;
    int width{}, height{};
    std::vector<std::vector<int>> tileData;
    std::vector<Collider> colliders;

// private:
//     SDL_FRect src{}, dest{};
//
//     SDL_Texture* Water = nullptr;
//     SDL_Texture* Dirt = nullptr;
//     SDL_Texture* Grass = nullptr;
//
//     int MapData[10][15]{};
};

#endif //COMP_8552_WEEK1_CLION_MAP_H