#include <cstdlib>
#include <string>
#include <vector>
#include "logic/cells.h"
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
    using namespace std;
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

    board_rect = Rectangle{
        200,
        30,
        960 - 200 - 30,
        540 - 30 - 30,
    };
    board_inner_rect = Rectangle{
        board_rect.x + separation * 2,
        board_rect.y + separation * 2,
        board_rect.width - separation * 4,
        board_rect.height - separation * 4,
    };
    cell_size = board_inner_rect.height / cell_num.y;

    if (this->state.difficulty != 2) {
        board_rect.x = (board_rect.x + board_rect.width) - board_rect.height;
        board_rect.width = board_rect.height;
        board_inner_rect.x = board_rect.x + separation * 2;
        board_inner_rect.width = board_inner_rect.height;
    } else {
        float real_width = cell_size * cell_num.x + separation * 4;
        board_rect.x = (board_rect.x + board_rect.width) - real_width;
        board_rect.width = real_width;
        board_inner_rect.x = board_rect.x + separation * 2;
        board_inner_rect.width = board_inner_rect.height;
    }

    cells_rects = vector<vector<Rectangle>>();
    for (int i = 0; i < cell_num.x; i++) {
        vector<Rectangle> rects_collumn = vector<Rectangle>();

        for (int j = 0; j < cell_num.y; j++) {
            Rectangle my_rect = Rectangle{
                board_inner_rect.x + (cell_size)*i,
                board_inner_rect.y + (cell_size)*j,
                (float)cell_size,
                (float)cell_size,
            };

            rects_collumn.push_back(my_rect);
        }
        cells_rects.push_back(rects_collumn);
    }
}

void GameScene::update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Use lambda for changing visibility
        check_cells_collision([this](int x, int y) {
            auto the_cell = state.my_engine->getCellInfo().at(x).at(y);
            the_cell.setVisible(true);
            state.my_engine->registerPlayerMove(x, y, the_cell);
        });
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        // Use lambda for toggle flag
        check_cells_collision([this](int x, int y) {
            auto the_cell = state.my_engine->getCellInfo().at(x).at(y);
            the_cell.toggleFlag();
            state.my_engine->registerPlayerMove(x, y, the_cell);
        });
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        // Use lambda to reveal flags adjacent to values
        check_cells_collision([this](int x, int y) {
            auto the_cell = state.my_engine->getCellInfo().at(x).at(y);
            if (the_cell.isVisible()) {
                return;
            }
            state.my_engine->revealAdjacentCells(x, y);
        });
    }

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
    DrawRectangleRec(board_rect, GRAY);             // Board background
    DrawRectangleLinesEx(board_rect, 3.0f, BLACK);  // Board borders
    draw_cells();
    // DEBUG
    // DrawRectangleLinesEx(board_inner_rect, 2.0f, RED);

    // ----- Draw User Interface -----
    GuiPanel(Rectangle{0, 0, 180, 540}, NULL);
}

SharedState GameScene::unload() {
    cells_rects.clear();
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

void GameScene::draw_cells() {
    using namespace std;

    for (size_t i = 0; i < cell_num.x; i++) {
        auto curr_collumn = cells_rects.at(i);

        for (size_t j = 0; j < cell_num.y; j++) {
            auto curr_cell_rect = curr_collumn.at(j);
            vector<vector<Cell>> engine_cells = state.my_engine->getCellInfo();

            if (!engine_cells.at(i).at(j).isVisible()) {
                // If it's hidden
                DrawRectangleRec(curr_cell_rect, DARKGRAY);
            } else if (engine_cells.at(i).at(j).isMined()) {
                // If it's not hidden but it's mined
                Vector2 middle = Vector2{
                    curr_cell_rect.x + curr_cell_rect.width / 2.0f,
                    curr_cell_rect.y + curr_cell_rect.height / 2.0f,
                };
                DrawCircleV(middle, curr_cell_rect.width / 2.5f, RED);
            } else {
                // If it's not hidden and empty
                Vector2 font_anchor = Vector2{
                    curr_cell_rect.x + curr_cell_rect.width / 4.0f,
                    curr_cell_rect.y + curr_cell_rect.height / 8.0f,
                };
                float font_size =
                    curr_cell_rect.height - (curr_cell_rect.height / 8.0f);

                auto digit = to_string(engine_cells.at(i).at(j).getValue());
                DrawTextEx(GetFontDefault(), digit.c_str(), font_anchor,
                           font_size, 1, RAYWHITE);
            }
            DrawRectangleLinesEx(curr_cell_rect, 5.0f, BLACK);
        }
    }
}

void GameScene::check_cells_collision(std::function<void(int, int)> action) {
    for (int i = 0; i < cells_rects.size(); ++i) {
        auto collumn = cells_rects.at(i);
        for (int j = 0; j < collumn.size(); ++j) {
            auto cell_rect = collumn.at(i);
            if (!CheckCollisionPointRec(GetMousePosition(), cell_rect)) {
                action(i, j);
                return;
            }
        }
    }
}
