#include <memory>
#include <vector>
#include "graphics/scenes.hpp"
#include "logic/engine.hpp"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

enum AppState {
    MainScreen,
    MainGame,
    GameOver,
};

class App {
   public:
    App() {
        state = AppState::MainScreen;
    }
    ~App() = default;

    void initialize_app() {
        scenes.push_back(new MainMenu());   // MainScreen
        scenes.push_back(new GameScene());  // MainGame
        auto scene_state = SharedState{
            std::make_unique<Engine>(),
            0,
        };
        scenes.at(this->state)->load(std::move(scene_state));
    }

    void deinitialize_app() {
        auto that_state = scenes.at(this->state)->unload();
        delete that_state.my_engine.release();

        for (size_t i = 0; i < this->scenes.size(); i++) {
            delete (this->scenes.at(i));
        }
    }

    void check_scene_change() {
        if (scenes.size() <= this->state ||
            !scenes.at(this->state)->should_change()) {
            return;
        }
        auto scene_state = scenes.at(this->state)->unload();
        switch (this->state) {
            case MainScreen:
                this->state = AppState::MainGame;
                break;
            case MainGame:
                this->state = AppState::MainScreen;
                break;
            case GameOver:
                break;
        }
        scenes.at(this->state)->load(std::move(scene_state));
    }

    bool should_quit() {
        return scenes.at(this->state)->should_quit();
    }

    void run_update_step() {
        if (scenes.size() <= this->state) {
            return;
        }
        scenes.at(this->state)->update();
    }

    void run_draw_step() {
        BeginDrawing();
        DrawFPS(20, 20);  // Debug
        if (scenes.size() <= this->state) {
            return;
        }
        scenes.at(this->state)->draw();
        EndDrawing();
    }

    AppState get_state() {
        return state;
    }

   private:
    AppState state;
    std::vector<Scene*> scenes;
};

int main(int argc, char* argv[]) {
    InitWindow(960, 540, "Buscaminas Estructurado");
    SetTargetFPS(60);

    App* my_app = new App();

    my_app->initialize_app();
    while (!WindowShouldClose() && !my_app->should_quit()) {
        my_app->check_scene_change();
        my_app->run_update_step();

        my_app->run_draw_step();
    }
    my_app->deinitialize_app();
    CloseWindow();
    delete my_app;
    return 0;
}
