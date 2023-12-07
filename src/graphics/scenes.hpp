#ifndef __Scene_Included__
#define __Scene_Included__
#include <memory>
#include <vector>
#include "../logic/engine.hpp"
#include "raylib.h"

namespace gfx {
struct Cell {
    Rectangle rect;
    bool hidden;
    bool bomb;
    bool flagged;
};
}  // namespace gfx

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
    virtual bool should_change() {
        return change_scene;
    }
    virtual bool should_quit() {
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
    SharedState unload();
    bool should_change();
    bool should_quit();

   private:
    SharedState state;
    Font font;
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
    bool should_change();
    bool should_quit();

   private:
    int calc_cell_size();

    SharedState state;
    Font font;
    std::vector<std::vector<bool>> cells;
    std::vector<gfx::Cell> cells_rect;
    Rectangle board_rect;
    Vector2 cell_num;
    int separation = 6;
    int cell_size;
    bool change_scene;
    bool quit_game;
};

/// Escena de Game Over con puntuaciones

#endif  // !__Scene_Included__
