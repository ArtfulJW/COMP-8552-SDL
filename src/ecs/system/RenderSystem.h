//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_RENDERSYSTEM_H
#define COMP_8552_WEEK1_CLION_RENDERSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "TextureManager.h"

class RenderSystem {
public:
    void render(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                auto& t = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();
                sprite.dst.x = t.position.x;
                sprite.dst.y = t.position.y;
                TextureManager::Draw(sprite.texture, sprite.src, sprite.dst);
            }
        }
    }
};

#endif //COMP_8552_WEEK1_CLION_RENDERSYSTEM_H