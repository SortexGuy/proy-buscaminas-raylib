#ifndef __Scene_Included__
#define __Scene_Included__
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "../logic/engine.hpp"
#include "raylib.h"

struct SharedState {
    std::unique_ptr<Engine> my_engine;
    int difficulty;
};

/// Clase abstracta de Escenas
class Scene {
    //! NUNCA crear una instancia de esta clase
   public:
    Scene() {
    }
    ~Scene() {
    }

    virtual void load(SharedState state) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual SharedState unload() = 0;
    virtual bool shouldChange() {
        return change_scene;
    }
    virtual bool shouldQuit() {
        return quit_game;
    }

    Font font;
    bool change_scene = false;
    bool quit_game = false;

   private:
};

/// Escena del menu principal
class MainMenu : public Scene {
   public:
    MainMenu();
    ~MainMenu();

    void load(SharedState state);
    void update();
    void draw();
    void drawMainUI(Vector2 anchor);
    void drawDificultyUI(Vector2 anchor);
    void drawHighScorePanel(Vector2 anchor);
    SharedState unload();
    bool shouldChange();
    bool shouldQuit();

   private:
    SharedState state;
    Font font;
    bool change_style = false;
    bool is_default_style = true;
    bool main_buttons_states[3];
    bool change_scene;
    bool quit_game;
};

/// Escena del juego
class GameScene : public Scene {
   public:
    GameScene();
    ~GameScene();

    void load(SharedState state);
    void update();
    void draw();
    SharedState unload();
    bool shouldChange();
    bool shouldQuit();

   private:
    int calcCellSize();
    void drawCells();
    void drawGui();
    void drawGameEndGui();
    void drawNameDialog();
    void checkCellsColls(std::function<void(int, int)> action);

    SharedState state;
    Font font;
    std::vector<std::vector<Rectangle>> cells_rects;
    std::string player_name = "";
    Rectangle board_rect;
    Rectangle board_inner_rect;
    Vector2 cell_num;
    bool name_confirmed = false;
    int separation = 2;
    float cell_size;
    bool change_scene = false;
    bool change_pause = false;
    bool quit_game = false;
};

/// Escena de Game Over con puntuaciones

#endif  // !__Scene_Included__
