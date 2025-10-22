//
// Created by User on 9/9/2025.
//

#include "Map.h"

#include <cmath>

#include "TextureManager.h"
#include <sstream>
#include <tinyxml2.h>

// int InMapData[10][15] {
//     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,1,1,2,0,0,0,0,0,0,0},
//     {0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
//     {0,0,0,0,0,2,2,2,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
// };
//
// Map::Map():
//     Water(TextureManager::Load("../Asset/water.png")),
//     Grass(TextureManager::Load("../Asset/grass.png")),
//     Dirt(TextureManager::Load("../Asset/dirt.png"))
// {
//     LoadMap(InMapData);
//
//     // What part of the image do we want?
//     src.x = src.y = 0;
//     src.w = src.h = 32;
//
//     // Where do we want to display it?
//     dest.x = dest.y = 0;
//
//     // How big do we want to display it?
//     dest.w = dest.h = 64;
// }
//
// Map::~Map() {
//     if (Water) SDL_DestroyTexture(Water);
//     if (Grass) SDL_DestroyTexture(Grass);
//     if (Dirt) SDL_DestroyTexture(Dirt);
// }
//
// void Map::LoadMap(int Data[10][15]) {
//     for (int row = 0; row < 10; row++) {
//         for (int col = 0; col < 15; col++) {
//             MapData[row][col] = Data[row][col];
//         }
//     }
// }

void Map::load(const char *path, SDL_Texture *ts) {
    tileset = ts;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    // Parse width and height of map
    auto* mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");

    // Parse terrain data
    auto* layer = mapNode->FirstChildElement("layer");
    auto* data = layer->FirstChildElement("data");

    std::string csv = data->GetText();
    std::stringstream ss(csv);
    tileData = std::vector(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::string val;
            // Read characters from string stream until it hits a comma, or is at the end of the stream.
            if (!std::getline(ss, val, ',')) break;

            // String to int converter (std::stoi)
            tileData[i][j] = std::stoi(val);
        }
    }

    // Parse collider data
    // auto* objectGroup = layer->NextSiblingElement("objectgroup");

    // Iterate through all elements that're objectgroup
    for (tinyxml2::XMLElement* element = layer->NextSiblingElement("objectgroup"); element != nullptr; element = element->NextSiblingElement("objectgroup")) {
        const char* objectGroupName = element->Attribute("name");
        if (strcmp(objectGroupName,"Collision Layer") == 0) {
            // Create a for loop with initialization, condition and an increment
            for (auto* obj = element->FirstChildElement("object"); obj != nullptr; obj = obj->NextSiblingElement("object")) {
                Collider c;
                c.rect.x = obj->FloatAttribute("x");
                c.rect.y = obj->FloatAttribute("y");
                c.rect.w = obj->FloatAttribute("width");
                c.rect.h = obj->FloatAttribute("height");
                colliders.push_back(c);
            }
        }
        else if (strcmp(objectGroupName,"Item Layer") == 0) {
            for (auto* obj = element->FirstChildElement("object"); obj != nullptr; obj = obj->NextSiblingElement("object")) {
                Transform t;
                t.position.x = obj->FloatAttribute("x");
                t.position.y = obj->FloatAttribute("y");
                t.oldPosition = t.position;
                t.scale = 1.0f;
                t.rotation = 0.0f;
                spawnPoints.push_back(t);
            }
        }

        // objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }

    // Create a for loop with initialization, condition and an increment
    // for (auto* obj = objectGroup->FirstChildElement("object"); obj != nullptr; obj = obj->NextSiblingElement("object")) {
    //     Collider c;
    //     c.rect.x = obj->FloatAttribute("x");
    //     c.rect.y = obj->FloatAttribute("y");
    //     c.rect.w = obj->FloatAttribute("width");
    //     c.rect.h = obj->FloatAttribute("height");
    //     colliders.push_back(c);
    // }
    //
    // auto* objectGroupTwo = objectGroup->NextSiblingElement("objectgroup");
    // for (auto* obj = objectGroupTwo->FirstChildElement("object"); obj != nullptr; obj = obj->NextSiblingElement("object")) {
    //     Transform t;
    //     t.position.x = obj->FloatAttribute("x");
    //     t.position.y = obj->FloatAttribute("y");
    //     t.oldPosition = t.position;
    //     t.scale = 1.0f;
    //     t.rotation = 0.0f;
    //     spawnPoints.push_back(t);
    // }
}


void Map::draw(const Camera& cam) {
    // int type = 0;

    SDL_FRect src{}, dest{};
    dest.w = dest.h = 32;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int type = tileData[row][col];

            float worldX = static_cast<float>(col) * dest.w;
            float worldY = static_cast<float>(row) * dest.h;

            // Move the tiles or map relative to the camera
            // Convert from world space to screen space
            dest.x = std::round(worldX - cam.view.x);
            dest.y = std::round(worldY - cam.view.y);

            switch (type) {
                case 1:
                    // Dirt
                    src.x = 0;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 2:
                    // Grass
                    src.x = 32;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 4:
                    // Water
                    src.x = 32;
                    src.y = 32;
                    src.w = 32;
                    src.h = 32;
                    break;
                default:
                    break;
            }

            TextureManager::Draw(tileset, src, dest);
        }
    }
}
