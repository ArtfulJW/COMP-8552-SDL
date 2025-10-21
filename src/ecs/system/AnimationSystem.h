//
// Created by User on 10/14/2025.
//

#ifndef COMP_8552_WEEK1_CLION_ANIMATIONSYSTEM_H
#define COMP_8552_WEEK1_CLION_ANIMATIONSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class Entity;

/*
 * State System : Deciding which animation to use
 * Check if the animation has been switched
 * Playback System: Advances the animation
 */

class AnimationSystem {
    public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& e : entities) {
            if (e->hasComponent<Animation>() && e->hasComponent<Velocity>()) {
                auto& anim = e->getComponent<Animation>();
                auto& velocity = e->getComponent<Velocity>();

                // State System ONLY FOR THE PLAYER TEMPORARY FIX
                std::string newClip = "idle";
                if (e->hasComponent<PlayerTag>()) {
                    if (velocity.direction.x > 0.0f) {
                        newClip = "walk_right";
                    }
                    else if (velocity.direction.x < 0.0f) {
                        newClip = "walk_left";
                    }
                    else if (velocity.direction.y > 0.0f) {
                        newClip = "walk_down";
                    }
                    else if (velocity.direction.y < 0.0f) {
                        newClip = "walk_up";
                    }
                    else {
                        newClip = "idle";
                    }
                }

                /*
                 * Now we're going to check if the animation has switched
                 * If the chose clip is different from the current one:
                 * 1. witch to the new clip
                 * 2. Reset Time and Frame Index
                 */
                if (newClip != anim.currentClip) {
                    // Switch to the new clip
                    anim.currentClip = newClip;

                    // Reset time to 0
                    anim.time = 0.0f;

                    // Reset the frame index to the beginning
                    anim.currentFrame = 0;
                }

                /*
                 * Playback System - Advance the Animation:
                 */

                // How long each animation frame lasts
                float animationFrameSpeed = anim.speed;

                // Get the currently played clip
                auto& clip = anim.clips[anim.currentClip];

                /*
                 * Every game loop frame, add delta time to this animation's elapsed time
                 */
                anim.time += dt;

                // Once enough time has passed, go to next 'animation frame'
                if (anim.time >= animationFrameSpeed) {
                    // Subtract frame speed from the elapsed time, so the extra time isn't lost
                    anim.time -= animationFrameSpeed;

                    std::size_t totalAnimationFrames = clip.frameIndices.size();

                    // Advance to the next animation frame
                    // Wrap around if it reaches the end of the clip
                    anim.currentFrame = (anim.currentFrame + 1) % totalAnimationFrames;
                }
            }
        }
    }
};

#endif //COMP_8552_WEEK1_CLION_ANIMATIONSYSTEM_H