//
// Created by super on 2025-10-02.
//

#ifndef COMP_8552_WEEK1_CLION_COLLISIONSYSTEM_H
#define COMP_8552_WEEK1_CLION_COLLISIONSYSTEM_H
#include <memory>
#include <vector>

#include "Entity.h"

class World;

class CollisionSystem
{
public:
    void update(World& world);

private:
    /*
     * Get the entities from the world, and get the ones that have the collider component
     */
    std::vector<Entity*> queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities);
};

#endif //COMP_8552_WEEK1_CLION_COLLISIONSYSTEM_H