#include "raygui.h"
#include "raylib.h"
#include "scenes.hpp"

MainMenu::MainMenu() {
    font = GetFontDefault();
}

MainMenu::~MainMenu() {
    UnloadFont(font);
}

void MainMenu::load(SharedState state) {
    this->state = std::move(state);
    for (bool& elem : main_buttons_states) {
        elem = false;
    }
}

void MainMenu::update() {
    if (change_style) {
        if (is_default_style) {
            GuiLoadStyle("../assets/style_cyber.rgs");
        } else {
            GuiLoadStyleDefault();
        }
        is_default_style = !is_default_style;
    }

    if (main_buttons_states[0]) {
        this->change_scene = true;
    }
    if (main_buttons_states[2]) {
        this->quit_game = true;
    }
}

void MainMenu::draw() {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_DISABLED)));
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

        GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
        main_anchor.x = 960 - 360;
        main_anchor.y = 540 - 360;
        GuiPanel(Rectangle{main_anchor.x, main_anchor.y, 330, 300},
                 "Mejor Puntuacion");

        GuiSetStyle(DEFAULT, TEXT_SIZE, 56);
        change_style =
            GuiButton(Rectangle{30, 480, 30, 30}, GuiIconText(ICON_GEAR, ""));
        GuiLock();
    } else {
        GuiUnlock();
        Rectangle container_rect = Rectangle{
            main_anchor.x,
            main_anchor.y,
            960 - (main_anchor.x) * 2,
            540 - (main_anchor.y) * 2,
        };
        Vector2 padding = Vector2{56, 24};

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

        if (GuiButton(Rectangle{main_anchor.x + padding.x,
                                main_anchor.y + padding.y + 80, 200, 200},
                      "8x8")) {
            // Se ha elegido la difficulty 8x8
            state.difficulty = 0;
            main_buttons_states[1] = false;
            return;
        } else if (GuiButton(
                       Rectangle{main_anchor.x + padding.x + 230,
                                 main_anchor.y + padding.y + 80, 200, 200},
                       "16x16")) {
            // Se ha elegido la difficulty 16x16
            state.difficulty = 1;
            main_buttons_states[1] = false;
            return;
        } else if (GuiButton(
                       Rectangle{main_anchor.x + padding.x + 460,
                                 main_anchor.y + padding.y + 80, 200, 200},
                       "24x16")) {
            // Se ha elegido la difficulty 24x16
            state.difficulty = 2;
            main_buttons_states[1] = false;
            return;
        }

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

SharedState MainMenu::unload() {
    this->state.my_engine->deinit();
    this->change_scene = false;
    this->quit_game = false;
    return std::move(this->state);
}

bool MainMenu::shouldChange() {
    return this->change_scene;
}

bool MainMenu::shouldQuit() {
    return this->quit_game;
}
