//
// Created by super on 2025-10-02.
//

#include "World.h"

#include <iostream>

#include "Game.h"

void subscribeFreeFunction(const CollisionEvent& collision) {
    // Make sure both entities in this collision event are valid
    if (collision.entityA == nullptr || collision.entityB == nullptr)
    {
        return;
    }

    // Check if both entities have colliders
    if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>()))
    {
        return;
    }

    auto& colliderA = collision.entityA->getComponent<Collider>();
    auto& colliderB = collision.entityB->getComponent<Collider>();

    Entity* player = nullptr;
    Entity* item = nullptr;

    if (colliderA.tag == "player" && colliderB.tag == "item")
    {
        player = collision.entityA;
        item = collision.entityB;
    }
    else if (colliderA.tag == "item" && colliderB.tag == "player")
    {
        player = collision.entityB;
        item = collision.entityA;
    }
    else {
        return;
    }

    std::cout << "A collision occurred between Entity A and Entity B" << std::endl;
}

World::World()
{
    // Subscribe to the collision events
    eventManager.subscribe([this](const CollisionEvent& collision)
    {
        Entity* sceneStateEntity = nullptr;

        // find scene state entity
        for (auto& e : entities) {
            if (e->hasComponent<SceneState>()) {
                sceneStateEntity = e.get();
                break;
            }
        }

        if (!sceneStateEntity) {
            return;
        }

        if (collision.entityA == nullptr || collision.entityB == nullptr)
        {
            return;
        }

        if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>()))
        {
            return;
        }

        auto& colliderA = collision.entityA->getComponent<Collider>();
        auto& colliderB = collision.entityB->getComponent<Collider>();

        Entity* player = nullptr;
        Entity* item = nullptr;
        Entity* wall = nullptr;
        Entity* projectile = nullptr;

        if (colliderA.tag == "player" && colliderB.tag == "item")
        {
            player = collision.entityA;
            item = collision.entityB;
        }
        else if (colliderA.tag == "item" && colliderB.tag == "player")
        {
            player = collision.entityB;
            item = collision.entityA;
        }

        if (player && item)
        {
            item->destroy();

            // scene state
            auto& sceneState = sceneStateEntity->getComponent<SceneState>();
            sceneState.coinsCollected++;

            if (sceneState.coinsCollected > 1) {
                Game::onSceneChangeRequest("Level2");
            }
        }

        // Player vs wall
        if (colliderA.tag == "player" && colliderB.tag == "wall")
        {
            player = collision.entityA;
            wall = collision.entityB;
        }
        else if (colliderA.tag == "wall" && colliderB.tag == "player")
        {
            player = collision.entityB;
            wall = collision.entityA;
        }

        if (player && wall) {
            // Stop the player
            auto& t = player->getComponent<Transform>();
            t.position = t.oldPosition;
        }

        // Player vs projectile
        if (colliderA.tag == "player" && colliderB.tag == "projectile")
        {
            player = collision.entityA;
            projectile = collision.entityB;
        }
        else if (colliderA.tag == "projectile" && colliderB.tag == "player")
        {
            player = collision.entityB;
            projectile = collision.entityA;
        }

        if (player && projectile) {
            player->destroy();
            // Change Scenes defer
            Game::onSceneChangeRequest("gameover");
        }

    });

    eventManager.subscribe(subscribeFreeFunction);
}
