//
// Created by User on 10/14/2025.
//

#include "AssetManager.h"

#include "tinyxml2.h"

std::unordered_map<std::string, Animation> AssetManager::animations;

void AssetManager::loadAnimation(const std::string &clipName, const char *path) {
    Animation animation = loadAnimationFromXML(path);
    animations[clipName] = animation;
}

const Animation &AssetManager::getAnimation(const std::string &clipName) {
    return animations[clipName];
}

Animation AssetManager::loadAnimationFromXML(const char *path) {
    Animation anim;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    auto* root = doc.FirstChildElement("animations");
    for (auto* clipElem = root->FirstChildElement(); clipElem; clipElem = clipElem->NextSiblingElement()) {
        std::string clipName = clipElem->Name();
        AnimationClip clip;

        for (auto* frameElem = clipElem->FirstChildElement("frame"); frameElem; frameElem = frameElem->NextSiblingElement()) {
            SDL_FRect rect;
            frameElem->QueryFloatAttribute("x", &rect.x);
            frameElem->QueryFloatAttribute("y", &rect.y);
            frameElem->QueryFloatAttribute("w", &rect.w);
            frameElem->QueryFloatAttribute("h", &rect.h);
            clip.frameIndices.push_back(rect);
        }
        anim.clips[clipName] = clip;
    }

    // Assuming there are actually entries in our clips, we're going to set the current clip to the beginning
    if (!anim.clips.empty()) {
        anim.currentClip = anim.clips.begin()->first;
    }

    return anim;
}
