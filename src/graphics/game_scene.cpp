#include <cstddef>
#include <cstdlib>
#include <functional>
#include <string>
#include <vector>
#include "fmt/core.h"
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

    int num_minas;
    function<Vector2(int)> get_cells_num = [&num_minas](int difficulty) {
        switch (difficulty) {
            case 1:
                num_minas = 30;
                return Vector2{16, 16};
            case 2:
                num_minas = 60;
                return Vector2{24, 16};
            case 0:
                num_minas = 10;
                break;
        }
        return Vector2{8, 8};
    };
    cell_num = get_cells_num(this->state.difficulty);
    cell_size = calcCellSize();

    this->state.my_engine->init(cell_num.x, cell_num.y, num_minas);

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
    if (IsKeyPressed(KEY_F1)) {
        this->change_scene = true;
    }
    if (IsKeyPressed(KEY_F2)) {
        this->quit_game = true;
    }

    if ((state.my_engine->isGameOver() || state.my_engine->didPlayerWin()) ||
        state.my_engine->getGamePaused()) {
        return;
    }
    // Update timer only if playing
    if (state.my_engine->isPlaying()) {
        state.my_engine->updateTimer(GetFrameTime());
    }
    // sumarle uno a la jugada
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Use lambda for changing visibility
        checkCellsColls([this](int x, int y) {
            Cell the_cell = state.my_engine->getCellInfo().at(x).at(y);
            if (the_cell.isVisible() || the_cell.isFlagged()) {
                return;
            }
            // cambio joey
            if (the_cell.getValue() == 0 && !the_cell.isMined()) {
                state.my_engine->revealAdjacentCells(x, y);
            }

            the_cell.setVisible(true);
            state.my_engine->registerPlayerMove(x, y, the_cell);
        });
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        // Use lambda for toggle flag
        checkCellsColls([this](int x, int y) {
            Cell the_cell = state.my_engine->getCellInfo().at(x).at(y);
            if (the_cell.isVisible()) {
                return;
            }
            the_cell.toggleFlag();
            state.my_engine->registerPlayerMove(x, y, the_cell);
        });
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        // Use lambda to reveal flags adjacent to values
        checkCellsColls([this](int x, int y) {
            Cell the_cell = state.my_engine->getCellInfo().at(x).at(y);
            if (!the_cell.isVisible()) {
                return;
            }
            state.my_engine->revealAdjacentCells(x, y);
            state.my_engine->registerPlayerMove(x, y, the_cell);
        });
    }
}

void GameScene::draw() {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_DISABLED)));

    if (state.my_engine->getGamePaused()) {
        // Draw paused screen
    } else {
        // ----- Board drawing -----
        DrawRectangleRec(board_rect,
                         GetColor(GuiGetStyle(
                             DEFAULT, BACKGROUND_COLOR)));  // Board background
        DrawRectangleLinesEx(
            board_rect, 2.2f,
            GetColor(
                GuiGetStyle(DEFAULT, BORDER_COLOR_FOCUSED)));  // Board borders
        drawCells();
    }

    // ----- Draw User Interface -----
    if (!name_confirmed ||
        (name_confirmed &&
         (state.my_engine->isGameOver() || state.my_engine->didPlayerWin()))) {
        GuiUnlock();
    }
    drawGui();
    GuiLock();
    if (state.my_engine->isGameOver() || state.my_engine->didPlayerWin()) {
        drawGameEndGui();
    }
}

SharedState GameScene::unload() {
    state.my_engine->saveGame(player_name);
    cells_rects.clear();
    change_scene = false;
    quit_game = false;
    name_confirmed = false;
    return std::move(this->state);
}

bool GameScene::shouldChange() {
    return this->change_scene;
}

bool GameScene::shouldQuit() {
    return this->quit_game;
}

int GameScene::calcCellSize() {
    return 40 / (cell_num.y / 8.0f);
}

void GameScene::drawCells() {
    using namespace std;

    // Lambda para guardar espacio horizontal
    auto draw_calls = [this](int x, int y, Rectangle curr_rect) {
        unique_ptr<Engine>& eng = state.my_engine;
        Cell curr_engine_cell = eng->getCellInfo().at(x).at(y);

        Color back_color = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));
        if (!curr_engine_cell.isVisible()) {
            // If it's hidden
            float contrast = 0.2f;
            if (!(eng->isGameOver() || eng->didPlayerWin()) &&
                !eng->getGamePaused() &&
                CheckCollisionPointRec(GetMousePosition(), curr_rect)) {
                contrast = 0.4f;
            }
            DrawRectangleRec(curr_rect, ColorContrast(back_color, contrast));

            if (curr_engine_cell.isFlagged()) {
                // Draw flag
                Rectangle triangle_rect = Rectangle{
                    curr_rect.x + (curr_rect.width * 0.25f),
                    curr_rect.y + (curr_rect.height * 0.2f),
                    curr_rect.width - (curr_rect.width * 0.5f),
                    curr_rect.height - (curr_rect.height * 0.6f),
                };
                DrawTriangle(
                    Vector2{triangle_rect.x, triangle_rect.y},
                    Vector2{triangle_rect.x,
                            triangle_rect.y + triangle_rect.height},
                    Vector2{triangle_rect.x + triangle_rect.width,
                            triangle_rect.y + (triangle_rect.height / 2.0f)},
                    RED);
                DrawRectangleRounded(
                    Rectangle{
                        curr_rect.x + (curr_rect.width * 0.2f),
                        curr_rect.y + (curr_rect.height * 0.2f),
                        curr_rect.width - (curr_rect.width * 0.85f),
                        curr_rect.height - (curr_rect.height * 0.4f),
                    },
                    0.8f, 24, BLACK);
            }
        } else if (curr_engine_cell.isMined()) {
            // If it's not hidden but it's mined
            Vector2 middle = Vector2{
                curr_rect.x + curr_rect.width / 2.0f,
                curr_rect.y + curr_rect.height / 2.0f,
            };
            DrawCircleV(middle, curr_rect.width / 2.5f, RED);
        } else {
            // If it's not hidden and empty
            DrawRectangleRec(curr_rect, back_color);
            Vector2 font_anchor = Vector2{
                curr_rect.x + curr_rect.width / 4.0f,
                curr_rect.y + curr_rect.height / 8.0f,
            };
            float font_size = curr_rect.height - (curr_rect.height / 8.0f);

            string digit = to_string(curr_engine_cell.getValue());
            DrawTextEx(GetFontDefault(), digit.c_str(), font_anchor, font_size,
                       1, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_FOCUSED)));
        }
        DrawRectangleLinesEx(
            curr_rect, 5.0f,
            GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL)));
    };

    for (size_t i = 0; i < cell_num.x; i++) {
        vector<Rectangle> curr_collumn = cells_rects.at(i);

        for (size_t j = 0; j < cell_num.y; j++) {
            Rectangle curr_cell_rect = curr_collumn.at(j);

            draw_calls(i, j, curr_cell_rect);
        }
    }
}

void GameScene::drawGui() {
    using namespace std;

    Rectangle panel_rect = Rectangle{0, 0, 180, 540};
    GuiPanel(panel_rect, NULL);
    Rectangle main_anchor = Rectangle{
        panel_rect.x + 16,
        panel_rect.y + 30,
        panel_rect.width - 32,
        panel_rect.height - 60,
    };

    Rectangle drawing_rect = Rectangle{
        main_anchor.x,
        main_anchor.y,
        main_anchor.width,
        58,
    };
    double timer = state.my_engine->getTime();
    int minutes = timer / 60;
    int seconds = (int)timer % 60;
    string timer_str = fmt::format("{:02}:{:02}", minutes, seconds);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
    GuiLabel(drawing_rect, timer_str.c_str());

    main_anchor.y += 130;
    drawing_rect = Rectangle{
        main_anchor.x,
        main_anchor.y,
        main_anchor.width,
        16,
    };
    int moves = state.my_engine->getMoves();  // state.my_engine.getMoves();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiLabel(drawing_rect, fmt::format("Jugadas\n\n[{: 03}]", moves).c_str());

    main_anchor.y += 100;
    drawing_rect = Rectangle{
        main_anchor.x,
        main_anchor.y,
        main_anchor.width,
        16,
    };
    int bombs_remaining =
        state.my_engine->getRemainingMines();  // state.my_engine.getMines();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiLabel(drawing_rect,
             fmt::format("Minas\n\n[{: 03}]", bombs_remaining).c_str());

    if ((state.my_engine->isGameOver() || state.my_engine->didPlayerWin()) &&
        !name_confirmed) {
        GuiDisable();
    }
    main_anchor = Rectangle{main_anchor.x, 540 - 70, 132, 66};
    drawing_rect = Rectangle{
        main_anchor.x + 8,
        main_anchor.y + 8,
        50,
        50,
    };

    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    this->change_scene = GuiButton(drawing_rect, GuiIconText(ICON_EXIT, ""));

    drawing_rect = Rectangle{
        main_anchor.x + 66 + 8,
        main_anchor.y + 8,
        50,
        50,
    };

    if (GuiButton(drawing_rect, GuiIconText(ICON_PLAYER_PAUSE, ""))) {
        state.my_engine->setGamePaused(!state.my_engine->getGamePaused());
    }
    GuiEnable();
}

void GameScene::checkCellsColls(std::function<void(int, int)> action) {
    for (int i = 0; i < cells_rects.size(); ++i) {
        std::vector<Rectangle> collumn = cells_rects.at(i);
        for (int j = 0; j < collumn.size(); ++j) {
            Rectangle cell_rect = collumn.at(j);
            // Error-correcting smaller rect
            cell_rect.x += cell_rect.width * 0.02f;
            cell_rect.y += cell_rect.width * 0.02f;
            cell_rect.width -= cell_rect.width * 0.04f;
            cell_rect.height -= cell_rect.width * 0.04f;
            auto mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, cell_rect)) {
                action(i, j);
                return;
            }
        }
    }
}

void GameScene::drawGameEndGui() {
    using namespace std;
    bool has_winned = state.my_engine->didPlayerWin();

    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiLabel(Rectangle{220, 120, 700, 280},
             has_winned ? "Has Ganado!!" : "Has Perdido!!");

    if (!name_confirmed) {
        GuiUnlock();
        drawNameDialog();
        GuiLock();
    }
}

void GameScene::drawNameDialog() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    Rectangle panel_rect = Rectangle{270, 380, 600, 120};
    GuiPanel(panel_rect, NULL);
    Rectangle main_anchor = Rectangle{
        panel_rect.x + 12,
        panel_rect.y + 16,
        panel_rect.width - 24,
        panel_rect.height - 48,
    };
    GuiGroupBox(main_anchor, "Introduce tu nombre");

    Rectangle drawing_rect = Rectangle{
        main_anchor.x + 6,
        main_anchor.y + 32,
        main_anchor.width - 12,
        24,
    };
    GuiSetStyle(TEXTBOX, TEXT_READONLY, false);
    char name_text[40] = "";
    player_name.copy(name_text, 40);
    GuiTextBox(drawing_rect, name_text, 40, true);
    player_name = name_text;

    drawing_rect.y = panel_rect.y + panel_rect.height - 28;
    name_confirmed = GuiButton(drawing_rect, "Confirmar");
}
