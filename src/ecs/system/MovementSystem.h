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
            if (entity->hasComponent<Transform>() && entity->hasComponent<Velocity>()) {
                auto& t = entity->getComponent<Transform>();
                auto& v = entity->getComponent<Velocity>();

                // Track previous frame's pos
                t.oldPosition = t.position;

                Vector2D directionVec = v.direction;

                // Normalize Vector
                directionVec.normalize();

                // Custom multiply operator for Vector2D
                Vector2D velocityVector = directionVec * v.speed;

                // Update Position
                t.position += velocityVector * deltaTime;
            }
        }
    }
};


#endif //COMP_8552_WEEK1_CLION_MOVEMENTSYSTEM_H