#include <iostream>
#include <thread>
#include "raylib.h"

enum AppState {
    MainScreen,
    MainGame,
    Pause,
    GameOver,
};

class App {
   public:
    App() {
        state = AppState::MainScreen;
    }
    ~App() = default;

    AppState get_state() {
        return state;
    }

   private:
    AppState state;
};

int main(int argc, char* argv[]) {
    InitWindow(960, 540, "Buscaminas Estructurado");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
    }
    CloseWindow();
    return 0;
}
