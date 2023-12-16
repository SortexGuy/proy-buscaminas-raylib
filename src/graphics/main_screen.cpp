#include "fmt/core.h"
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

    GuiUnlock();
    if (!main_buttons_states[1]) {
        drawMainUI(main_anchor);
    } else {
        drawDificultyUI(main_anchor);
    }
    GuiLock();
}

void MainMenu::drawMainUI(Vector2 anchor) {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
    GuiLabel(Rectangle{anchor.x, anchor.y, 480, 50}, "Bienvenido al");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 82);
    GuiLabel(Rectangle{anchor.x, anchor.y + 60, 480, 82}, "Buscaminas");

    GuiSetStyle(DEFAULT, TEXT_SIZE, 56);
    main_buttons_states[0] =
        GuiButton(Rectangle{anchor.x, anchor.y + 170, 200, 70}, "Jugar");
    main_buttons_states[1] =
        GuiButton(Rectangle{anchor.x, anchor.y + 250, 300, 70}, "Dificultad");
    main_buttons_states[2] =
        GuiButton(Rectangle{anchor.x, anchor.y + 330, 200, 70}, "Salir");

    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    anchor.x = 960 - 420;
    anchor.y = 540 - 380;
    GuiPanel(Rectangle{anchor.x, anchor.y, 400, 270}, "Mejor Puntuacion");
    drawHighScorePanel(anchor);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 64);
    change_style =
        GuiButton(Rectangle{30, 480, 30, 30}, GuiIconText(ICON_EYE_ON, ""));
}

void MainMenu::drawDificultyUI(Vector2 anchor) {
    Rectangle container_rect = Rectangle{
        anchor.x,
        anchor.y,
        960 - (anchor.x) * 2,
        540 - (anchor.y) * 2,
    };
    Vector2 padding = Vector2{56, 24};

    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
    GuiPanel(container_rect, NULL);
    GuiLabel(
        Rectangle{
            anchor.x + padding.x,
            anchor.y + padding.y,
            300,
            50,
        },
        "Dificultad");

    if (GuiButton(Rectangle{anchor.x + padding.x, anchor.y + padding.y + 80,
                            200, 200},
                  "8x8")) {
        // Se ha elegido la difficulty 8x8
        state.difficulty = 0;
        main_buttons_states[1] = false;
        return;
    } else if (GuiButton(Rectangle{anchor.x + padding.x + 230,
                                   anchor.y + padding.y + 80, 200, 200},
                         "16x16")) {
        // Se ha elegido la difficulty 16x16
        state.difficulty = 1;
        main_buttons_states[1] = false;
        return;
    } else if (GuiButton(Rectangle{anchor.x + padding.x + 460,
                                   anchor.y + padding.y + 80, 200, 200},
                         "24x16")) {
        // Se ha elegido la difficulty 24x16
        state.difficulty = 2;
        main_buttons_states[1] = false;
        return;
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    main_buttons_states[1] = !GuiButton(
        Rectangle{
            anchor.x + padding.x,
            anchor.y + container_rect.height - (50 + padding.y),
            150,
            50,
        },
        "Atras");
}

void MainMenu::drawHighScorePanel(Vector2 anchor) {
    Data highscore = state.my_engine->getPlayerHighestScore();
    if (highscore.score < 0 && highscore.namePlayer.empty()) {
        return;
    }
    int text_size = 24;

    anchor.x += 16;
    anchor.y += 16;
    GuiSetStyle(DEFAULT, TEXT_SIZE, text_size);
    GuiLabel(Rectangle{anchor.x, anchor.y, 480, 50},
             fmt::format("{}", highscore.namePlayer).c_str());

    anchor.y += 30;
    GuiSetStyle(DEFAULT, TEXT_SIZE, text_size);
    GuiLabel(Rectangle{anchor.x, anchor.y, 480, 50},
             fmt::format("Puntuaje: {}", (long)highscore.score).c_str());

    anchor.y += 30;
    GuiSetStyle(DEFAULT, TEXT_SIZE, text_size);
    GuiLabel(
        Rectangle{anchor.x, anchor.y, 480, 50},
        fmt::format("Tiempo: {}:{}", highscore.time / 60, highscore.time % 60)
            .c_str());

    anchor.y += 30;
    GuiSetStyle(DEFAULT, TEXT_SIZE, text_size);
    GuiLabel(
        Rectangle{anchor.x, anchor.y, 480, 50},
        fmt::format("Minas encontradas: {}", highscore.foundMines).c_str());

    anchor.y += 30;
    GuiSetStyle(DEFAULT, TEXT_SIZE, text_size);
    GuiLabel(Rectangle{anchor.x, anchor.y, 480, 50},
             fmt::format("Dificultad: {}", highscore.difficulty).c_str());
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
