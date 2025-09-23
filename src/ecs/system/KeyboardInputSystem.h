//
// Created by User on 9/23/2025.
//

#ifndef COMP_8552_WEEK1_CLION_KEYBOARDINPUTSYSTEM_H
#define COMP_8552_WEEK1_CLION_KEYBOARDINPUTSYSTEM_H
#include <memory>
#include <vector>
#include <SDL3/SDL_events.h>

#include "Component.h"
#include "Entity.h"

/*
 * The purpose of the KeyboardInputSystem is to refer to SDL (who tells us what keys are being pressed), and
 * change the DIRECTION of the player accordingly. KeyboardInputSystem is only responsible for manipulating
 * DIRECTIONS.
 */
class KeyboardInputSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const SDL_Event& event) {
        for (auto& e : entities) {
            if (e->hasComponent<Velocity>()) {
                auto& v = e->getComponent<Velocity>();
                if (event.type == SDL_EVENT_KEY_DOWN) {
                    switch (event.key.key) {
                        case SDLK_W:
                            v.direction.y = -1;
                            break;
                        case SDLK_S:
                            v.direction.y = 1;
                            break;
                        case SDLK_A:
                            v.direction.x = -1;
                            break;
                        case SDLK_D:
                            v.direction.x = 1;
                            break;
                        default:
                            break;
                    }
                }

                // Resetting the direction if key is not pressed.
                if (event.type == SDL_EVENT_KEY_UP) {
                    switch (event.key.key) {
                        case SDLK_W:
                            v.direction.y = 0;
                            break;
                        case SDLK_S:
                            v.direction.y = 0;
                            break;
                        case SDLK_A:
                            v.direction.x = 0;
                            break;
                        case SDLK_D:
                            v.direction.x = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
};

#endif //COMP_8552_WEEK1_CLION_KEYBOARDINPUTSYSTEM_H