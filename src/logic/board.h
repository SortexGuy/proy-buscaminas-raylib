#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "cells.h"

class Board {
   public:
    Board(int width, int height);
    Board();
    ~Board();

    void generateBoard();
    void mostrarMinasTablero();
    void revealCells(int x, int y);
    void revealAdjNotFlaggedCells(int x, int y);
    void placeFlag(int x, int y);
    void removeFlag(int x, int y);
    std::vector<std::vector<Cell>> getCells() const;
    void setCellInfo(int x, int y, Cell new_cell);
    void clear();
    int countMinesBoard();
    int countMinesDiscovered();
    int countRevealedSafeCells();
    int boardSize();
    void revealAdjacentCells(int x, int y);
    bool checkGameOver ();
    bool checkWin();


   private:
    int id;
    int numMine;
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;

    void putMine();
    void countAdjacentMines(int x, int y);
};

#endif  // BOARD_H
