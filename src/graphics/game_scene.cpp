#include <cstdlib>
#include <vector>
#include "raygui.h"
#include "raylib.h"
#include "scenes.hpp"

GameScene::GameScene() {
    font = GetFontDefault();
}

GameScene::~GameScene() {
    UnloadFont(font);
}

void GameScene::load(SharedState state) {
    this->state = std::move(state);
    // ----- DEBUG -----
    auto get_cells_num = [](int difficulty) {
        switch (difficulty) {
            case 1:
                return Vector2{16, 16};
            case 2:
                return Vector2{24, 16};
            case 0:
                break;
        }
        return Vector2{8, 8};
    };
    cell_num = get_cells_num(this->state.difficulty);
    cell_size = calc_cell_size();
    // ----- DEBUG -----
    this->state.my_engine->init(cell_num.x, cell_num.y);

    board_rect = Rectangle{
        200,
        30,
        960 - 200 - 30,
        540 - 30 - 30,
    };

    cells = std::vector<std::vector<bool>>(
        cell_num.x, std::vector<bool>(cell_num.y, false));

    // Vector2 board_size = Vector2{
    //     cell_num.x * (cell_size + separation * 2) + separation * 2.0f,
    //     cell_num.y * (cell_size + separation * 2) + separation * 2.0f,
    // };
    // board_rect = Rectangle{
    //     (960 - board_size.x) * (9.0f / 10.0f),
    //     (540 - board_size.y) * (3.0f / 4.0f),
    //     board_size.x,
    //     board_size.y,
    // };

    Vector2 start_pos = Vector2{
        board_rect.x + separation * 2,
        board_rect.y + separation * 2,
    };

    cell_size =
        (board_rect.height - separation * 2) / (cell_num.y + separation * 2);

    for (size_t i = 0; i < cells.size(); i++) {
        std::vector<bool> collumn = cells.at(i);

        for (size_t j = 0; j < collumn.size(); j++) {
            Rectangle my_rect = Rectangle{
                start_pos.x + (cell_size + separation * 2) * i,
                start_pos.y + (cell_size + separation * 2) * j,
                (float)cell_size,
                (float)cell_size,
            };

            bool hidden = (i * j) % 10 > std::rand() % 15;
            auto my_cell = gfx::Cell{my_rect, hidden, collumn.at(j), false};
            cells_rect.push_back(my_cell);
        }
    }
}

void GameScene::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        this->change_scene = true;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        this->quit_game = true;
    }
}

void GameScene::draw() {
    ClearBackground(LIGHTGRAY);
    // if (is_paused()) {
    //     // Draw paused screen
    //     return;
    // }

    // ----- Board drawing -----
    DrawRectangleRounded(board_rect, 0.05f, 8, GRAY);
    DrawRectangleRoundedLines(board_rect, 0.05f, 8, 3.0f, BLACK);
    for (size_t i = 0; i < cells_rect.size(); i++) {
        auto curr_cell = cells_rect.at(i);
        if (curr_cell.hidden) {
            DrawRectangleRounded(curr_cell.rect, 0.4f, 8, DARKGRAY);
        } else if (curr_cell.bomb) {
            Vector2 middle = Vector2{
                curr_cell.rect.x + curr_cell.rect.width / 2.0f,
                curr_cell.rect.y + curr_cell.rect.height / 2.0f,
            };
            DrawCircleV(middle, curr_cell.rect.width / 2.5f, RED);
        } else {
            Vector2 start_pos = Vector2{
                curr_cell.rect.x + curr_cell.rect.width / 4.0f,
                curr_cell.rect.y + curr_cell.rect.height / 8.0f,
            };
            float font_size =
                curr_cell.rect.height - (curr_cell.rect.height / 8.0f);
            DrawTextEx(GetFontDefault(), "0", start_pos, font_size, 1,
                       RAYWHITE);
        }
        DrawRectangleRoundedLines(curr_cell.rect, 0.4f, 8, 5.0f, BLACK);
    }

    // ----- Draw User Interface -----
    GuiPanel(Rectangle{0, 0, 120, 540}, NULL);
}

SharedState GameScene::unload() {
    cells.clear();
    cells_rect.clear();
    this->change_scene = false;
    this->quit_game = false;
    return std::move(this->state);
}

bool GameScene::should_change() {
    return this->change_scene;
}

bool GameScene::should_quit() {
    return this->quit_game;
}

int GameScene::calc_cell_size() {
    return 40 / (cell_num.y / 8.0f);
}
