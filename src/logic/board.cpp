#include "board.h"
#include <random>
#include <vector>
#include "cells.h"
#include "raylib.h"
#include "raymath.h"

// enviar un tablero y dificulta
// dificulta 0 8x8 1 16x16 2 24x16

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;
}

Board::Board() {
}

Board::~Board() {
}

void Board::generateBoard() {
    cells.resize(width, std::vector<Cell>(height));

    putMine();

    // Calcular y establecer los valores de las celdas adyacentes a las minas
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (!cells[i][j].isMined()) {
                CountAdjacentMines(i, j);
            }
        }
    }
}

std::vector<std::vector<Cell>> Board::getCells() const {
    return cells;
}

void Board::clear(){
    cells.clear();
}

void Board::putMine() {
    using namespace std;

    int mineCount = 0;

    while (mineCount < 10) {
        int x = rand() % width;
        int y = rand() % height;
        if (!cells[x][y].isMined()) {
            cells[x][y].setIsMine(true);
            mineCount++;
        }
    }
}

void Board::RevealAdjacentCells(int x, int y) {
    cells.at(x).at(y).setIsVisible(true);

    int newx = 0;
    int newy = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            newx = x + i;
            newy = y + j;

            // verificar si la celda esta en los limites
            if (newx >= 0 && newx < width && newy >= 0 && newy < height) {
                if (cells.at(newx).at(newy).isVisible()) {
                    continue;
                }
                if (cells.at(newx).at(newy).getValue() == 0) {
                    RevealAdjacentCells(newx, newy);
                } else {
                    cells.at(newx).at(newy).setIsVisible(true);
                }
            }
        }
    }
}

void Board::CountAdjacentMines(int x, int y) {
    if (cells.at(x).at(y).isMined()) {
        return;
    }

    int mineCount = 0;
    int newx = 0;
    int newy = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            newx = x + i;
            newy = y + j;

            if (newx >= 0 && newx < width && newy >= 0 && newy < height) {
                if (cells.at(newx).at(newy).isMined()) {
                    mineCount++;
                }
            }
        }
    }
    cells.at(x).at(y).setValue(mineCount);
}

void Board::RevealCells(int x, int y) {
    cells.at(x).at(y).setIsVisible(true);

    if (!cells.at(x).at(y).isMined()) {
        if (cells.at(x).at(y).getValue() == 0) {
            RevealAdjacentCells(x, y);
        }
    }
    // game over o algo
}

void Board::placeFlag(int x, int y) {
    cells.at(x).at(y).setFlag(true);
}

void Board::removeFlag(int x, int y) {
    cells.at(x).at(y).setFlag(false);
}
