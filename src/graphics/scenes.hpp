#ifndef __Scene_Included__
#define __Scene_Included__
#include <vector>
#include "raylib.h"

namespace gfx {
struct Cell {
    Rectangle rect;
    bool hidden;
    bool bomb;
    bool flagged;
};
}  // namespace gfx

/// Clase abstracta de Escenas
class Scene {
    //! NUNCA crear una instancia de esta clase
   public:
    Scene() {
        // this->load();
    }
    ~Scene() {
        // this->unload();
    }

    virtual void load() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void unload() = 0;
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

    void load();
    void update();
    void draw();
    void unload();
    bool should_change();
    bool should_quit();

   private:
    bool main_buttons_states[3];
    Font font;
    bool change_scene;
    bool quit_game;
};

/// Escena del juego
class GameScene : public Scene {
   public:
    GameScene();
    ~GameScene();

    void load();
    void update();
    void draw();
    void unload();
    bool should_change();
    bool should_quit();

   private:
    int calc_cell_size();

    Font font;
    std::vector<std::vector<bool>> cells;
    std::vector<gfx::Cell> cells_rect;
    Rectangle board_rect;
    Vector2 cell_num = Vector2{24, 16};
    int cell_size = 40 / (cell_num.y / 8.0f);
    int separation = 5;
    bool change_scene;
    bool quit_game;
};

/// Escena de Game Over con puntuaciones

#endif  // !__Scene_Included__
