#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "board.h"

class Engine {
   public:
    Engine();
    ~Engine();

    // int scene = 0;  // 0: menu principal; 1:Pantalla de juego
    void init(int width, int height, int numMine);
    void deinit();
    bool registerPlayerMove(int x, int y, Cell cell_info);
    bool revealAdjacentCells(int x, int y);
    void updateTimer(double deltaTime);
    double getTime();
    std::vector<std::vector<Cell>> getCellInfo() const;

    void save_game(std::string player_name);  // Se necesita implementar

    void setPlaying(bool val);
    bool isPlaying();

    bool isGameOver();
    bool didPlayerWin();

    void setGamePaused(bool gamePaused);
    bool getGamePaused();

    int getMines();
    int getMoves();

   private:
    Board board;
    double timer = 0;
    bool playing = false;
    int movesPlayed = 0;
    bool gamePaused = false;
};

#endif  // ENGINE_H
