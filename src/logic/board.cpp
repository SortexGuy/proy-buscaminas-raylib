#include "board.h"
#include <random>
#include <vector>
#include "cells.h"

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
                countAdjacentMines(i, j);
            }
        }
    }
}

std::vector<std::vector<Cell>> Board::getCells() const {
    return cells;
}

void Board::clear() {
    cells.clear();
}

void Board::putMine() {
    using namespace std;

    int mineCount = 0;

    while (mineCount < 10) {
        int x = rand() % width;
        int y = rand() % height;
        if (!cells[x][y].isMined()) {
            cells[x][y].setHasMine(true);
            mineCount++;
        }
    }
}

void Board::revealAdjacentCells(int x, int y) {
    cells.at(x).at(y).setVisible(true);

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
                    revealAdjacentCells(newx, newy);
                } else {
                    cells.at(newx).at(newy).setVisible(true);
                }
            }
        }
    }
}

void Board::countAdjacentMines(int x, int y) {
    if (cells.at(x).at(y).isMined()) {
        return;
    }

    int mineCount = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            int newx = x + i;
            int newy = y + j;
            if (newx == 0) {  // Debug
            }
            if (newx < 0 || newx >= width || newy < 0 || newy >= height) {
                continue;
            }
            if (cells.at(newx).at(newy).isMined()) {
                mineCount++;
            }
        }
    }
    cells.at(x).at(y).setValue(mineCount);
}

void Board::revealCells(int x, int y) {
    cells.at(x).at(y).setVisible(true);

    if (!cells.at(x).at(y).isMined()) {
        if (cells.at(x).at(y).getValue() == 0) {
            revealAdjacentCells(x, y);
        }
    }
    // game over o algo
}
void Board::setCellInfo(int x, int y, Cell new_cell) {
    cells.at(x).at(y) = new_cell;
}

void Board::revealAdjNotFlaggedCells(int x, int y) {
    int newX, newY;

    if (!cells[x][y].isVisible() || cells[x][y].getValue() <= 0) {
        return;
    }
    int flagsCount = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            newX = x + i;
            newY = y + j;
            if (cells.at(newX).at(newY).isFlagged()) {
                flagsCount++;
            }
        }
    }

    if (flagsCount < cells.at(x).at(y).getValue()) {
        return;
    }
    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            if (k == 0 && l == 0) {
                continue;
            }

            newX = x + k;
            newY = y + l;

            if (cells.at(newX).at(newY).isFlagged() ||
                cells.at(newX).at(newY).isVisible()) {
                continue;
            }
            cells.at(newX).at(newY).setVisible(true);

            if (cells.at(newX).at(newY).isMined()) {
                // game over o algo
            }
        }
    }
}

int Board::countMinesBoard() {
    int count = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (cells.at(x).at(y).isMined()) {
                count++;
            }
            if (cells.at(x).at(y).isFlagged()) {
                count--;
            }
        }
    }

    return count;
}

// No necesarias
void Board::placeFlag(int x, int y) {
    cells.at(x).at(y).setFlag(true);
}

void Board::removeFlag(int x, int y) {
    cells.at(x).at(y).setFlag(false);
}
