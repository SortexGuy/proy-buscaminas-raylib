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
        return quitting;
    }

    Font font;
    bool quitting = false;

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

   private:
    Font font;
    bool quitting;
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

   private:
    Font font;
    std::vector<std::vector<bool>> cells;
    std::vector<gfx::Cell> cells_rect;
    Rectangle board_rect;
    int cell_num = 8;
    int cell_size = 40;
    int separation = 5;
    bool quitting;
};

/// Escena de Game Over con puntuaciones

#endif  // !__Scene_Included__
