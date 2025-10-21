//
// Created by User on 10/21/2025.
//

#ifndef COMP_8552_WEEK1_CLION_SCENE_H
#define COMP_8552_WEEK1_CLION_SCENE_H
#include <SDL3/SDL_events.h>

#include "World.h"

class Scene {
public:
    Scene(const char* sceneName, const char* mapPath, int windowWidth, int windowHeight);

    void update(const float dt ,const SDL_Event &e) {
        world.update(dt, e);
    }

    void render() {
        world.render();
    }

    World world;

    const std::string& getName() const {return name;}

private:
    std::string name;

    void createProjectile(Vector2D pos, Vector2D dir, int speed) {
    }
};

#endif //COMP_8552_WEEK1_CLION_SCENE_H