//
// Created by User on 10/21/2025.
//

#include "Scene.h"

#include "AssetManager.h"

Scene::Scene(const char *sceneName, const char *mapPath, int windowWidth, int windowHeight) : name(sceneName){

    world.getMap().load(mapPath, TextureManager::Load("../Asset/tileset.png"));
    for (auto& collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto& c = e.addComponent<Collider>("wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        // Have a visual of colliders
        SDL_Texture* tex = TextureManager::Load("../Asset/tileset.png");
        SDL_FRect colSrc {0, 32, 32, 32};
        SDL_FRect colDst {c.rect.x, c.rect.y, c.rect.w, c.rect.h};
        e.addComponent<Sprite>(tex, colSrc, colDst);
    }
    // map = new Map();
    // player = new GameObject("../Asset/ball.png", 0, 0);

    // Add Entities
    for (auto& transform : world.getMap().spawnPoints) {
        auto& item(world.createEntity());
        auto& itemTransform = item.addComponent<Transform>(Vector2D(transform.position.x, transform.position.y), 0.0f, 1.0f);
        SDL_Texture* itemTex = TextureManager::Load("../asset/coin.png");
        SDL_FRect itemSrc {0,0,32,32};
        SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y, 32, 32};
        item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
        auto& itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDest.w;
        itemCollider.rect.h = itemDest.h;
    }

    auto& cam = world.createEntity();
    SDL_FRect camView;
    camView.w = windowWidth;
    camView.h = windowHeight;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0,0), 0.0f, 1.0f);
    auto& playerVelocity = player.addComponent<Velocity>(Vector2D(0,0), 240.0f);

    Animation anim = AssetManager::getAnimation("player");
    player.addComponent<Animation>(anim);

    // No longer using Mario
    // SDL_Texture* tex = TextureManager::Load("../asset/mario.png");
    // SDL_FRect playerSrc{0,0,32,44};

    SDL_Texture* tex = TextureManager::Load("../asset/animations/Swordsman_walk.png");
    SDL_FRect playerSrc = anim.clips[anim.currentClip].frameIndices[0]; // Get the first frame of the current clip
    SDL_FRect playerDst{playerTransform.position.x,playerTransform.position.y,64,64};
    player.addComponent<Sprite>(tex, playerSrc, playerDst);
    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    // Add player tag
    player.addComponent<PlayerTag>();

    auto& spawner(world.createEntity());
    Transform t = spawner.addComponent<Transform>(Vector2D(windowWidth/2,windowHeight - 5), 0.0f, 1.0f);
    spawner.addComponent<TimedSpawner>(2.0, [this, t] {
        // Create our projectile here
        auto& e(world.createDeferredEntity());
        e.addComponent<Transform>(Vector2D(t.position.x,t.position.y), 0.0f, 1.0f);
        e.addComponent<Velocity>(Vector2D(0,-1), 100.0f);

        Animation anim = AssetManager::getAnimation("enemy");
        e.addComponent<Animation>(anim);

        SDL_Texture* tex = TextureManager::Load("../asset/animations/bird_anim.png");
        SDL_FRect src{0, 0, 32, 32};
        SDL_FRect dest{t.position.x, t.position.y, 32, 32};
        e.addComponent<Sprite>(tex, src, dest);

        Collider c = e.addComponent<Collider>("projectile");
        c.rect.w = dest.w;
        c.rect.h = dest.h;

        e.addComponent<ProjectileTag>();
    });

    // Add SceneState
    auto& state(world.createEntity());
    state.addComponent<SceneState>();

}
