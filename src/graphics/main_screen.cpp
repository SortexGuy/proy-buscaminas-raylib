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
    ClearBackground(LIGHTGRAY);
    DrawTextEx(font, "Bienvenido al", Vector2{960 / 10.0f, 540 / 7.0f}, 48, 4,
               RAYWHITE);
    DrawTextEx(font, "Buscaminas", Vector2{960 / 10.0f, 540 / 4.0f}, 82, 4,
               RAYWHITE);
    DrawTextEx(font, "Jugar", Vector2{960 / 10.0f, 540 / 2.0f}, 56, 4,
               RAYWHITE);
    DrawTextEx(font, "Salir", Vector2{960 / 10.0f, 540 / 1.6f}, 56, 4,
               RAYWHITE);
}

void MainMenu::unload() {
    this->quitting = false;
}

bool MainMenu::should_change() {
    return this->quitting;
}
