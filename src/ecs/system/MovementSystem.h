//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_MOVEMENTSYSTEM_H
#define COMP_8552_WEEK1_CLION_MOVEMENTSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"


class MovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Position>()) {
                auto& position = entity->getComponent<Position>();
                position.x += 60 * deltaTime;
                position.y += 60 * deltaTime;
            }
        }
    }
};


#endif //COMP_8552_WEEK1_CLION_MOVEMENTSYSTEM_H