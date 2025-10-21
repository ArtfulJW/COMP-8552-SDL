//
// Created by User on 10/21/2025.
//

#ifndef COMP_8552_WEEK1_CLION_SPAWNTIMERSYSTEM_H
#define COMP_8552_WEEK1_CLION_SPAWNTIMERSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class SpawnTimerSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, const float dt) {
        for (auto& entity : entities) {
            if (entity->hasComponent<TimedSpawner>()) {
                auto& spawner = entity->getComponent<TimedSpawner>();

                spawner.timer -= dt;
                if (spawner.timer <= 0) {
                    spawner.timer = spawner.spawnInterval; // (e.g. 2 seconds)
                    spawner.spawnCallback();
                }
            }
        }
    }
};

#endif //COMP_8552_WEEK1_CLION_SPAWNTIMERSYSTEM_H