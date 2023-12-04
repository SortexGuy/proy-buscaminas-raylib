#include "raygui.h"
#include "raylib.h"
#include "scenes.hpp"

MainMenu::MainMenu() {
    font = GetFontDefault();
}

MainMenu::~MainMenu() {
    UnloadFont(font);
}

void MainMenu::load() {
    for (auto& elem : main_buttons_states) {
        elem = false;
    }
}

void MainMenu::update() {
    if (main_buttons_states[0]) {
        this->change_scene = true;
    }
    if (main_buttons_states[2]) {
        this->quit_game = true;
    }
}

void MainMenu::draw() {
    ClearBackground(LIGHTGRAY);
    Vector2 main_anchor = Vector2{96, 76};

    GuiSetStyle(DEFAULT, TEXT_SPACING, 4);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_CENTER);

    if (!main_buttons_states[1]) {
        GuiUnlock();
        GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
        GuiLabel(Rectangle{main_anchor.x, main_anchor.y, 480, 50},
                 "Bienvenido al");
        GuiSetStyle(DEFAULT, TEXT_SIZE, 82);
        GuiLabel(Rectangle{main_anchor.x, main_anchor.y + 60, 480, 82},
                 "Buscaminas");

        GuiSetStyle(DEFAULT, TEXT_SIZE, 56);
        main_buttons_states[0] = GuiButton(
            Rectangle{main_anchor.x, main_anchor.y + 170, 200, 70}, "Jugar");
        main_buttons_states[1] =
            GuiButton(Rectangle{main_anchor.x, main_anchor.y + 250, 300, 70},
                      "Dificultad");
        main_buttons_states[2] = GuiButton(
            Rectangle{main_anchor.x, main_anchor.y + 330, 200, 70}, "Salir");
        GuiLock();
    } else {
        GuiUnlock();
        auto container_rect = Rectangle{
            main_anchor.x,
            main_anchor.y,
            960 - (main_anchor.x) * 2,
            540 - (main_anchor.y) * 2,
        };
        auto padding = Vector2{56, 24};

        GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
        GuiPanel(container_rect, NULL);
        GuiLabel(
            Rectangle{
                main_anchor.x + padding.x,
                main_anchor.y + padding.y,
                300,
                50,
            },
            "Dificultad");
        GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
        main_buttons_states[1] = !GuiButton(
            Rectangle{
                main_anchor.x + padding.x,
                main_anchor.y + container_rect.height - (50 + padding.y),
                150,
                50,
            },
            "Atras");
        GuiLock();
    }
}

void MainMenu::unload() {
    this->change_scene = false;
    this->quit_game = false;
}

bool MainMenu::should_change() {
    return this->change_scene;
}

bool MainMenu::should_quit() {
    return this->quit_game;
}
