#include <vector>
#include "raylib.h"
#include "scenes.hpp"

GameScene::GameScene() {
}
GameScene::~GameScene() {
}

void GameScene::load() {
    cells = std::vector<std::vector<bool>>(8, std::vector<bool>(8, false));
}

void GameScene::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        this->quitting = true;
    }
}

void GameScene::draw() {
    ClearBackground(GRAY);
    // for (size_t i = 0; i < cells.size(); i++) {
    // int x = i*
    // Rectangle my_rect = Rectangle{};
    // DrawRectangleRoundedLines(Rectangle rec, float roundness, int
    // segments,
    //                           float lineThick, Color color)
    // }
}

void GameScene::unload() {
    cells.clear();
    this->quitting = false;
}

bool GameScene::should_change() {
    return this->quitting;
}
