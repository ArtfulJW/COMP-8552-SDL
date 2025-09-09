//
// Created by User on 9/9/2025.
//

#include "Map.h"
#include "TextureManager.h"

int InMapData[10][15] {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,2,2,2,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map():
    Water(TextureManager::Load("../Asset/water.png")),
    Grass(TextureManager::Load("../Asset/grass.png")),
    Dirt(TextureManager::Load("../Asset/dirt.png"))
{
    LoadMap(InMapData);

    // What part of the image do we want?
    src.x = src.y = 0;
    src.w = src.h = 32;

    // Where do we want to display it?
    dest.x = dest.y = 0;

    // How big do we want to display it?
    dest.w = dest.h = 64;
}

Map::~Map() {
    if (Water) SDL_DestroyTexture(Water);
    if (Grass) SDL_DestroyTexture(Grass);
    if (Dirt) SDL_DestroyTexture(Dirt);
}

void Map::LoadMap(int Data[10][15]) {
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            MapData[row][col] = Data[row][col];
        }
    }
}

void Map::DrawMap() {
    int type = 0;

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            type = MapData[row][col];

            dest.x = col * 64;
            dest.y = row * 64;

            switch (type) {
                case 0:
                    TextureManager::Draw(Water, src, dest);
                    break;
                case 1:
                    TextureManager::Draw(Dirt, src, dest);
                    break;
                case 2:
                    TextureManager::Draw(Grass, src, dest);
                    break;
                default:
                    break;
            }
        }
    }
}
