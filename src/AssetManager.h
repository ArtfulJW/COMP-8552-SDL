//
// Created by User on 10/14/2025.
//

#ifndef COMP_8552_WEEK1_CLION_ASSETMANAGER_H
#define COMP_8552_WEEK1_CLION_ASSETMANAGER_H
#include <string>
#include <unordered_map>

#include "Component.h"

class AssetManager {

    static std::unordered_map<std::string, Animation> animations;
    static Animation loadAnimationFromXML(const char* path);

public:
    static void loadAnimation(const std::string& clipName, const char* path);
    static const Animation& getAnimation(const std::string& clipName);

};

#endif //COMP_8552_WEEK1_CLION_ASSETMANAGER_H