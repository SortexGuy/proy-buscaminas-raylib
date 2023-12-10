#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "cells.h"

class Board {
   public:
    Board(int width, int height);
    ~Board();

    void generateBoard();
    void mostrarMinasTablero();
    void RevealCells(int x, int y);
    void placeFlag(int x, int y);
    void removeFlag(int x, int y);

   private:
    int id;
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;

    void ponerMines();
    void RevealAdjacentCells(int x, int y);
    void CountAdjacentMines(int x, int y);
};

#endif  // BOARD_H
