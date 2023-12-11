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

void GameScene::load(SharedState incoming_state) {
    this->state = std::move(incoming_state);

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

    this->state.my_engine->init(cell_num.x, cell_num.y);
    this->state.my_engine->getCellInfo();

    board_rect = Rectangle{
        200,
        30,
        960 - 200 - 30,
        540 - 30 - 30,
    };
    init_easy_game();
}

void GameScene::update() {
    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    //     for (auto& collumn : cells_rects) {
    //         for (auto& cell_rect : collumn) {
    //             if (!CheckCollisionPointRec(GetMousePosition(), cell_rect)) {
    //                 return;
    //             }
    //         }
    //     }
    // }
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
    draw_cells();

    // ----- Draw User Interface -----
    GuiPanel(Rectangle{0, 0, 120, 540}, NULL);
}

SharedState GameScene::unload() {
    cells.clear();
    cells_rect.clear();
    change_scene = false;
    quit_game = false;
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

void GameScene::init_easy_game() {
    using namespace std;

    vector<vector<Cell>> my_cells = state.my_engine->getCellInfo();
    Vector2 start_pos = Vector2{
        board_rect.x + separation * 2,
        board_rect.y + separation * 2,
    };

    cell_size =
        (board_rect.height - separation * 2) / (cell_num.y + separation * 2);

    cells_rects = vector<vector<Rectangle>>();
    for (size_t i = 0; i < cell_num.x; i++) {
        auto collumn = my_cells.at(i);
        vector<Rectangle> rects_collumn = vector<Rectangle>();

        for (size_t j = 0; j < cell_num.y; j++) {
            Rectangle my_rect = Rectangle{
                start_pos.x + (cell_size + separation * 2) * i,
                start_pos.y + (cell_size + separation * 2) * j,
                (float)cell_size,
                (float)cell_size,
            };

            rects_collumn.push_back(my_rect);
        }
        cells_rects.push_back(rects_collumn);
    }
}

void GameScene::draw_cells() {
    using namespace std;

    for (size_t i = 0; i < cell_num.x; i++) {
        auto curr_collumn = cells_rects.at(i);

        for (size_t j = 0; j < cell_num.y; j++) {
            auto curr_cell_rect = curr_collumn.at(i);
            vector<vector<Cell>> engine_cells = state.my_engine->getCellInfo();

            // if (curr_cell.hidden) {
            //     DrawRectangleRounded(curr_cell.rect, 0.4f, 8, DARKGRAY);
            // } else if (curr_cell.bomb) {
            //     Vector2 middle = Vector2{
            //         curr_cell.x + curr_cell.width / 2.0f,
            //         curr_cell.y + curr_cell.height / 2.0f,
            //     };
            //     DrawCircleV(middle, curr_cell.width / 2.5f, RED);
            // } else {
            Vector2 start_pos = Vector2{
                curr_cell_rect.x + curr_cell_rect.width / 4.0f,
                curr_cell_rect.y + curr_cell_rect.height / 8.0f,
            };
            float font_size =
                curr_cell_rect.height - (curr_cell_rect.height / 8.0f);
            DrawTextEx(GetFontDefault(), "0", start_pos, font_size, 1,
                       RAYWHITE);
            // }
            DrawRectangleRoundedLines(curr_cell_rect, 0.4f, 8, 5.0f, BLACK);
        }
    }
}
