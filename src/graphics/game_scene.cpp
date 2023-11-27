#include "raylib.h"
#include "scenes.hpp"

void GameScene::load() {
}

void GameScene::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        this->quitting = true;
    }
}

void GameScene::draw() {
    ClearBackground(BLUE);
}

void GameScene::unload() {
    this->quitting = false;
}

bool GameScene::should_change() {
    return this->quitting;
}
