#ifndef ENGINE_H
#define ENGINE_H

#include "board.h"
#include "raylib.h"
#include "raymath.h"

class Engine {
   public:
    Engine();
    ~Engine();

    // int scene = 0;  // 0: menu principal; 1:Pantalla de juego
    void init(int width, int height);
    void deInit();
    std::vector<std::vector<Cell>> getCellInfo() const;

   private:
    Board board;
};

#endif  // ENGINE_H
