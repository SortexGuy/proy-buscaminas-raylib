#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "storage/gamestatus.h"
#include "storage/savearchive.h"
#include "board.h"


class Engine {
   public:
    Engine();
    ~Engine();

    void init(int width, int height, int numMine);
    void deinit();
    bool registerPlayerMove(int x, int y, Cell cell_info);
    bool revealAdjacentCells(int x, int y);
    void updateTimer(double deltaTime);
    double getTime();
    std::vector<std::vector<Cell>> getCellInfo() const;

    void saveGame(std::string player_name);  // Se necesita implementar


    void setPlaying(bool val);
    bool isPlaying();

    bool isGameOver();
    bool didPlayerWin();

    void setGamePaused(bool gamePaused);
    bool getGamePaused();

    int getMines();
    int getMoves();

    void calcularPuntuaje();
    string dificulta();

   private:
    Board board;
    SavedArchive savedArchive;
    double timer = 0;
    bool playing = false;
    int movesPlayed = 0;
    bool gamePaused = false;
    double score = 0;
};

#endif  // ENGINE_H
