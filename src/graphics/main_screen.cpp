#include "raylib.h"
#include "scenes.hpp"

MainMenu::MainMenu() {
    font = GetFontDefault();
}

MainMenu::~MainMenu() {
    UnloadFont(font);
}

void MainMenu::load() {
}

void MainMenu::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        this->quitting = true;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
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
