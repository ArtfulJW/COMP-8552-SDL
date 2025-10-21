//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_WORLD_H
#define COMP_8552_WEEK1_CLION_WORLD_H
#include <future>
#include <memory>
#include <vector>

#include "AnimationSystem.h"
#include "CameraSystem.h"
#include "CollisionSystem.h"
#include "DestructionSystem.h"
#include "Entity.h"
#include "EventManager.h"
#include "KeyboardInputSystem.h"
#include "Map.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "SpawnTimerSystem.h"

class World {
private:
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> deferredEntities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem KeyboardInputSystem;
    CollisionSystem collisionSystem;
    AnimationSystem animationSystem;
    CameraSystem cameraSystem;
    EventManager eventManager;
    SpawnTimerSystem spawnTimerSystem;
    DestructionSystem destructionSystem;

public:
    World();

    void update(float deltaTime, const SDL_Event& event) {
        KeyboardInputSystem.update(entities, event);
        movementSystem.update(entities, deltaTime);
        collisionSystem.update(*this);
        animationSystem.update(entities, deltaTime);
        cameraSystem.update(entities);
        spawnTimerSystem.update(entities, deltaTime);
        destructionSystem.update(entities);
        synchronizeEntities();
        cleanup();
    }

    void render() {

        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                map.draw(entity->getComponent<Camera>());
                break;
            }
        }

        renderSystem.render(entities);
    }

    Entity& createEntity() {
        // Use emplace instaed of push so we don't create a copy.
        entities.emplace_back(std::make_unique<Entity>());

        return *entities.back();
    }

    Entity& createDeferredEntity() {
        deferredEntities.emplace_back(std::make_unique<Entity>());
        return *deferredEntities.back();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

    void cleanup() {
        // use a lambda predicate to remove all inactive entities
        std::erase_if(
            entities,
            [](std::unique_ptr<Entity>& e) {
                return !e->isActive();
            });
    }

    void synchronizeEntities() {
        if (!deferredEntities.empty()) {
            // push back all deferred entities to the entities vector
            // using move so we don't create a copy
            std::move(deferredEntities.begin(), deferredEntities.end(), std::back_inserter(entities));
            // clearing the creation buffer
            deferredEntities.clear();
        }
    }

    EventManager& getEventManager()
    {
        return eventManager;
    }

    Map& getMap() { return map; }
};

#endif //COMP_8552_WEEK1_CLION_WORLD_H