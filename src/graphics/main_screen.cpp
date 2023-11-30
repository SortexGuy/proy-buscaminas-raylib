#include "raylib.h"
#include "scenes.hpp"

MainMenu::MainMenu() {
}
MainMenu::~MainMenu() {
}

void MainMenu::load() {
}

void MainMenu::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        this->quitting = true;
    }
}

void MainMenu::draw() {
    ClearBackground(RED);
}

void MainMenu::unload() {
    this->quitting = false;
}

bool MainMenu::should_change() {
    return this->quitting;
}
