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
Board::Board(){
}

Board::~Board() {
}

void Board::generateBoard() {
    cells.resize(height, std::vector<Cell>(width));

    putMine();

    // Calcular y establecer los valores de las celdas adyacentes a las minas
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!cells[i][j].isMined()) {
                CountAdjacentMines(i, j);
            }
        }
    }
}

std::vector<std::vector<Cell>> Board::getCells() const {
    return cells;
}

void Board::putMine() {
    using namespace std;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribX(0, width - 1);
    uniform_int_distribution<int> distribY(0, height - 1);

    int mineCount = 0;

    while (mineCount < 10) {
        int x = distribX(gen);
        int y = distribY(gen);
        if (!cells[y][x].isMined()) {
            cells[y][x].setIsMine(true);
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
                if (cells.at(newx).at(newy).getIsVisible()) {
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

    if (cells.at(x).at(y).isFlagged()){
        removeFlag(x,y);
    }
    else{
        cells.at(x).at(y).setIsVisible(true);
        
        if (!cells.at(x).at(y).isMined()) {
            if (cells.at(x).at(y).getValue() == 0) {
            RevealAdjacentCells(x, y);
        }
    }
    // game over o algo
    }
    
}

void Board::placeFlag(int x, int y) {
    cells.at(x).at(y).setFlag(true);
}

void Board::removeFlag(int x, int y) {
    cells.at(x).at(y).setFlag(false);
}
