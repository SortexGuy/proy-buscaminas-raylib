#include <cstdlib>
#include <vector>
#include "raylib.h"
#include "scenes.hpp"

GameScene::GameScene() {
    font = GetFontDefault();
}

GameScene::~GameScene() {
    UnloadFont(font);
}

void GameScene::load() {
    cells = std::vector<std::vector<bool>>(8, std::vector<bool>(8, false));

    int board_size = cell_num * (cell_size + separation * 2) + separation * 2;
    board_rect = Rectangle{
        960 / 2.0f - board_size / 2.0f,
        (540 - board_size) * (3.0f / 4.0f),
        (float)board_size,
        (float)board_size,
    };

    Vector2 start_pos = Vector2{
        board_rect.x + separation * 2,
        board_rect.y + separation * 2,
    };
    for (size_t i = 0; i < cells.size(); i++) {
        std::vector<bool> row = cells.at(i);

        for (size_t j = 0; j < row.size(); j++) {
            Rectangle my_rect = Rectangle{
                start_pos.x + (cell_size + separation * 2) * i,
                start_pos.y + (cell_size + separation * 2) * j,
                (float)cell_size,
                (float)cell_size,
            };

            bool hidden = (i * j) % 10 > std::rand() % 15;
            auto my_cell = gfx::Cell{my_rect, hidden, row.at(j), false};
            cells_rect.push_back(my_cell);
        }
    }
}

void GameScene::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        this->quitting = true;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
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
    DrawRectangleRoundedLines(board_rect, 0.05f, 8, 4.0f, BLACK);
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
        DrawRectangleRoundedLines(curr_cell.rect, 0.4f, 8, 4.0f, BLACK);
    }
}

void GameScene::unload() {
    cells.clear();
    cells_rect.clear();
    this->quitting = false;
}

bool GameScene::should_change() {
    return this->quitting;
}
