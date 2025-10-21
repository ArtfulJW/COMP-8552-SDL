//
// Created by User on 10/21/2025.
//

#ifndef COMP_8552_WEEK1_CLION_SCENEMANAGER_H
#define COMP_8552_WEEK1_CLION_SCENEMANAGER_H
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "Scene.h"

struct SceneParams {
    const char* name;
    const char* mapPath;
    int windowWidth;
    int windowHeight;
};

class SceneManager {
    std::unordered_map<std::string, SceneParams> sceneParams;
    std::string pendingScene;

    void changeScene(const std::string& name) {
        std::unordered_map<std::string, SceneParams>::iterator it = sceneParams.find(name);
        if (it != sceneParams.end()) {
            const auto& params = it->second;

            // Create scene object
            currentScene = std::make_unique<Scene>(params.name, params.mapPath, params.windowWidth, params.windowHeight);
        } else {
            std::cerr << "Scene " << name << " not found!" << std::endl;
        }
    }
public:
    std::unique_ptr<Scene> currentScene;

    void loadScene(const char* sceneName, const char* mapPath, int windowWidth, int windowHeight) {
        sceneParams[sceneName] = {sceneName, mapPath, windowWidth, windowHeight};
    }

    void changeSceneDeferred(const std::string& name) {
        pendingScene = name;
    }

    void update(const float dt, const SDL_Event& e) {
        if (currentScene) {
            currentScene->update(dt, e); // All world updates
        }
        if (!pendingScene.empty()) {
            changeScene(pendingScene);
            pendingScene.clear();
        }
    }

    void render() const {
        if (currentScene) {
            currentScene->render();
        }
    }
};

#endif //COMP_8552_WEEK1_CLION_SCENEMANAGER_H