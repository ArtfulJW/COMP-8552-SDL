//
// Created by User on 9/9/2025.
//

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *path, int x, int y):
xPos(x), yPos(y), texture(TextureManager::Load(path))
{

}

GameObject::~GameObject() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void GameObject::update(float deltaTime) {
    // xPos++;
    // yPos++;

    // Moving the player with DeltaTime
    xPos = xPos + 100 * deltaTime;
    yPos = yPos + 100 * deltaTime;

    // Where do we want to crop the texture from
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;

    // How much to crop?
    dstRect.w = dstRect.h = 32;

    dstRect.x = xPos;
    dstRect.y = yPos;
}

void GameObject::draw() {
    TextureManager::Draw(texture, srcRect, dstRect);
}
