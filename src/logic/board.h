#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include "cells.h"

class Board {
   public:
    Board(int width, int height, int numMine);
    Board();
    ~Board();

    void generateBoard();
    void revealAdjNotFlaggedCells(int x, int y);
    std::vector<std::vector<Cell>> getCells() const;
    void setCellInfo(int x, int y, Cell new_cell);
    void clear();
    int countMinesBoard();
    int countMinesDiscovered();
    int countRevealedSafeCells();
    void revealAdjacentCells(int x, int y);
    bool checkGameOver();
    bool checkWin();
    int countMineAndFlag();
    std::string indicateDifficulty();

   private:
    int numMine;
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;

    void putMine();
    void countAdjacentMines(int x, int y);
};

#endif  // BOARD_H
