//
// Created by User on 10/21/2025.
//

#ifndef COMP_8552_WEEK1_CLION_DESTRUCTIONSYSTEM_H
#define COMP_8552_WEEK1_CLION_DESTRUCTIONSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class DestructionSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* cameraEntity = nullptr;

        // Find the camera
        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                cameraEntity = entity.get();
                break;
            }
        }

        if (!cameraEntity) {
            return;
        }

        auto& cam = cameraEntity->getComponent<Camera>();
        for (auto& e : entities) {
            if (e->hasComponent<Transform>() && e->hasComponent<ProjectileTag>()) {
                auto& t = e->getComponent<Transform>();

                if (t.position.x > cam.view.x + cam.view.w || // right edge of the view
                    t.position.x < cam.view.x || // left edge
                    t.position.y > cam.view.y + cam.view.h || // bottom
                    t.position.y < cam.view.y) { // top
                    e->destroy();
                }
            }
        }

    }
};

#endif //COMP_8552_WEEK1_CLION_DESTRUCTIONSYSTEM_H