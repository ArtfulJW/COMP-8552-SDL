//
// Created by super on 2025-10-02.
//

#include "World.h"

#include <iostream>

World::World()
{
    // Subscribe to the collision events
    eventManager.subscribe<CollisionEvent>([](const CollisionEvent& collision)
    {
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
        }
    });

    eventManager.subscribe<CollisionEvent>([](const CollisionEvent& collision)
    {
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

        std::cout << "A collision occurred between Entity A and Entity B" << std::endl;
    });
}
