//
// Created by User on 9/16/2025.
//

#ifndef COMP_8552_WEEK1_CLION_WORLD_H
#define COMP_8552_WEEK1_CLION_WORLD_H
#include <memory>
#include <vector>

#include "CollisionSystem.h"
#include "Entity.h"
#include "EventManager.h"
#include "KeyboardInputSystem.h"
#include "Map.h"
#include "MovementSystem.h"
#include "RenderSystem.h"

class World {
private:
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem KeyboardInputSystem;
    CollisionSystem collisionSystem;
    EventManager eventManager;
public:
    World();

    void update(float deltaTime, const SDL_Event& event) {
        KeyboardInputSystem.update(entities, event);
        movementSystem.update(entities, deltaTime);
        collisionSystem.update(*this);
        cleanup();
    }

    void render() {
        map.draw();
        renderSystem.render(entities);
    }

    Entity& createEntity() {
        // Use emplace instaed of push so we don't create a copy.
        entities.emplace_back(std::make_unique<Entity>());

        return *entities.back();
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

    EventManager& getEventManager()
    {
        return eventManager;
    }

    Map& getMap() { return map; }
};

#endif //COMP_8552_WEEK1_CLION_WORLD_H