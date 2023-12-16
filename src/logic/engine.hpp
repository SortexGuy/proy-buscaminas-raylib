#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "board.h"
#include "storage/game_saver.hpp"

class Engine {
   public:
    Engine();
    ~Engine();

    void init(int width, int height, int numMine);
    void deinit();
    void registerPlayerMove(int x, int y, Cell cell_info);
    void revealAdjacentCells(int x, int y);
    void updateTimer(double deltaTime);
    double getTime();
    std::vector<std::vector<Cell>> getCellInfo() const;

    void saveGame(std::string player_name);  

    void setPlaying(bool val);
    bool isPlaying();

    bool isGameOver();
    bool didPlayerWin();

    void setGamePaused(bool gamePaused);
    bool getGamePaused();

    int getRemainingMines();
    int getMoves();

    void calculateScore();
    Data getPlayerHighestScore();

   private:
    Board board;
    GameSaver data = GameSaver();
    double timer = 0;
    bool playing = false;
    double score = 0;
    int cache_remaining_mines = 0;
    int last_move_checked = 0;
    int moves_played = 0;
    bool game_paused = false;
};

#endif  // ENGINE_H
