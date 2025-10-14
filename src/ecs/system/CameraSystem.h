//
// Created by User on 10/14/2025.
//

#ifndef COMP_8552_WEEK1_CLION_CAMERASYSTEM_H
#define COMP_8552_WEEK1_CLION_CAMERASYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class CameraSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* playerEntity = nullptr;

        // Find the Player
        for (auto& e : entities) {
            if (e->hasComponent<PlayerTag>()) {
                playerEntity = e.get();
                break;
            }
        }

        if (!playerEntity) {
            return;
        }

        auto& playerTransform = playerEntity->getComponent<Transform>();
        for (auto& e : entities) {
            if (e->hasComponent<Camera>()) {

                auto& cam = e->getComponent<Camera>();

                // This positons the camera so that the player is in the center
                cam.view.x = playerTransform.position.x - cam.view.w / 2;
                cam.view.y = playerTransform.position.y - cam.view.h / 2;

                // clamp the camera so that the player stays within the center
                if (cam.view.x < 0) {
                    cam.view.x = 0;
                }
                if (cam.view.y < 0) {
                    cam.view.y = 0;
                }

                if (cam.view.x > cam.worldWidth - cam.view.w) {
                    cam.view.x = cam.worldWidth - cam.view.w;
                }
                if (cam.view.y > cam.worldHeight - cam.view.h) {
                    cam.view.y = cam.worldHeight - cam.view.h;
                }
            }
        }
    }
};

#endif //COMP_8552_WEEK1_CLION_CAMERASYSTEM_H