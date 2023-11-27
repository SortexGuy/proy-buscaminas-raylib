#ifndef __Scene_Included__
#define __Scene_Included__

/// Clase abstracta de Escenas
class Scene {
    //! NUNCA crear una instancia de esta clase
   public:
    Scene() {
        this->load();
    }
    ~Scene() {
        this->unload();
    }

    virtual void load() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void unload() = 0;
    virtual bool should_change() {
        return quitting;
    }
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
    bool quitting;
};

/// Escena de Game Over con puntuaciones

#endif  // !__Scene_Included__
