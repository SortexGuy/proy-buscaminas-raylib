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
    void deinit();
    bool registerPlayerMove(int x, int y, Cell cell_info);
    bool revealAdjacentCells(int x, int y);
    void updateTimer(double deltaTime);
    double getTime();
    void setPlaying(bool val);
    bool isPlaying();
    std::vector<std::vector<Cell>> getCellInfo() const;

   private:
    Board board;
    double timer = 0;
    bool playing = false;
    bool movesPlayed = 0;
};

#endif  // ENGINE_H
