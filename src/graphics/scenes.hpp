#ifndef __Scene_Included__
#define __Scene_Included__

class Scene {
   public:
    Scene();
    ~Scene();

    virtual void load() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void unload() = 0;
    virtual bool should_change() {
        return quitting;
    }

   private:
    bool quitting = false;
};

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
};

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
};

#endif  // !__Scene_Included__
