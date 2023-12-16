#include "board.h"
#include <random>
#include <string>
#include <vector>
#include "cells.h"

// Constructor
Board::Board(int width, int height, int numMine) {
    this->width = width;
    this->height = height;
    this->numMine = numMine;
}
// Constructor
Board::Board() {
}
// Destructor
Board::~Board() {
}

// Genera el tablero de juego.
void Board::generateBoard() {
    // Redimensionar el vector de celdas para que coincida con el ancho y alto.
    cells.resize(width, std::vector<Cell>(height));

    // Colocar las minas en el tablero.
    putMine();

    // Calcular y establecer los valores de las celdas adyacentes a las minas
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (!cells[i][j].isMined()) {
                countAdjacentMines(i, j);
            }
        }
    }
}  // Genera el tablero de juego.

// Devuelve las celdas del tablero.
std::vector<std::vector<Cell>> Board::getCells() const {
    return cells;
}

// Limpia todas las celdas del tablero.
void Board::clear() {
    cells.clear();
}

void Board::putMine() {
    using namespace std;

    int mineCount = 0;

    // Ciclo hasta que se coloquen todas las minas deseadas
    while (mineCount < numMine) {
        // Generar coordenadas aleatorias dentro del tablero
        int x = rand() % width;
        int y = rand() % height;

        // Verificar si la celda en las coordenadas generadas ya tiene una mina
        if (!cells[x][y].isMined()) {
            // Colocar una mina en la celda
            cells[x][y].setHasMine(true);
            mineCount++;
        }
    }
}

void Board::revealAdjacentCells(int x, int y) {
    // Si el valor de la celda no es cero, retornar
    if (cells.at(x).at(y).getValue() != 0) {
        return;
    }

    // Establecer la celda actual como visible
    cells.at(x).at(y).setVisible(true);

    int newx = 0;
    int newy = 0;

    // Iterar sobre las celdas adyacentes
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Saltar la celda actual
            if (i == 0 && j == 0) {
                continue;
            }

            newx = x + i;
            newy = y + j;

            // Verificar si la celda adyacente está dentro de los límites del
            // tablero
            if (newx >= 0 && newx < width && newy >= 0 && newy < height) {
                // Saltar si la celda adyacente ya es visible
                if (cells.at(newx).at(newy).isVisible()) {
                    continue;
                }

                // Si el valor de la celda adyacente es cero, revelar
                // recursivamente sus celdas adyacentes
                if (cells.at(newx).at(newy).getValue() == 0) {
                    revealAdjacentCells(newx, newy);
                } else {
                    // Establecer la celda adyacente como visible
                    cells.at(newx).at(newy).setVisible(true);
                }
            }
        }
    }
}

// Esta función cuenta el número de minas adyacentes para una celda dada
void Board::countAdjacentMines(int x, int y) {
    // Si la celda actual tiene una mina, se retorna
    if (cells.at(x).at(y).isMined()) {
        return;
    }

    // Inicializar mineCount en 0
    int mineCount = 0;

    // Iterar sobre las celdas adyacentes
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Saltar la celda actual
            if (i == 0 && j == 0) {
                continue;
            }

            // Calcular las coordenadas de la celda adyacente
            int newx = x + i;
            int newy = y + j;

            // Verificar si la celda adyacente está dentro de los límites del
            // tablero
            if (newx < 0 || newx >= width || newy < 0 || newy >= height) {
                continue;
            }

            // Si la celda adyacente tiene una mina, se incrementa mineCount
            if (cells.at(newx).at(newy).isMined()) {
                mineCount++;
            }
        }
    }

    // Establecer el valor de la celda actual en mineCount
    cells.at(x).at(y).setValue(mineCount);
}

// Establece la información de la celda en las coordenadas especificadas.
void Board::setCellInfo(int x, int y, Cell new_cell) {
    cells.at(x).at(y) = new_cell;
}

// Revela las celdas adyacentes que no están marcadas.
void Board::revealAdjNotFlaggedCells(int x, int y) {
    // Verifica si el valor de la celda es 0
    if (cells.at(x).at(y).getValue() == 0) {
        return;
    }

    int newX, newY;

    int flagsCount = 0;
    // Cuenta el número de celdas adyacentes marcadas.
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            newX = x + i;
            newY = y + j;
            // Verifica si la celda adyacente está dentro de los límites del
            // tablero.
            if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
                continue;
            }
            // Verifica si la celda adyacente está marcada.
            if (cells.at(newX).at(newY).isFlagged()) {
                flagsCount++;
            }
        }
    }

    // Verifica si el número de celdas adyacentes marcadas es menor que el valor
    // de la celda.
    if (flagsCount < cells.at(x).at(y).getValue()) {
        return;
    }
    // Revela las celdas adyacentes que no están marcadas ni visibles.
    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            if (k == 0 && l == 0) {
                continue;
            }

            newX = x + k;
            newY = y + l;

            // Verifica si la celda adyacente está dentro de los límites del
            // tablero.
            if (newX < 0 || newX >= width || newY < 0 || newY >= height) {
                continue;
            }
            // Verifica si la celda adyacente está marcada o ya es visible.
            if (cells.at(newX).at(newY).isFlagged() ||
                cells.at(newX).at(newY).isVisible()) {
                continue;
            }

            // Establece la celda adyacente como visible.
            cells.at(newX).at(newY).setVisible(true);
            // Si el valor de la celda adyacente es 0, revela recursivamente sus
            // celdas adyacentes.
            if (cells.at(newX).at(newY).getValue() == 0) {
                revealAdjacentCells(newX, newY);
            }
        }
    }
}

// Devuelve el número de minas en el tablero.
int Board::countMinesBoard() {
    return numMine;
}

// Cuenta el número de minas
// Y descuenta el numero de banderas
int Board::countMinesDiscovered() {
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

// Cuenta el número de celdas que están minadas y marcadas en el tablero
int Board::countMineAndFlag() {
    int count = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (cells.at(x).at(y).isMined() && cells.at(x).at(y).isFlagged()) {
                count++;
            }
        }
    }
    return count;
}

// Cuenta el número de celdas seguras reveladas en el tablero
int Board::countRevealedSafeCells() {
    int count = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (cells.at(x).at(y).isVisible()) {
                count++;
            }
        }
    }
    return count;
}

// indica la dificultad del tablero
std::string Board::indicateDifficulty() {
    int calculo = (width * height);
    switch (calculo) {
        case (24 * 16):
            return "Dificil";
            break;
        case (16 * 16):
            return "Media";
            break;
        default:  // case (8 * 8):
            return "Facil";
            break;
    }
}

// Verifica si el juego ha terminado
bool Board::checkGameOver() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (cells.at(i).at(j).isVisible() && cells.at(i).at(j).isMined()) {
                return true;
            }
        }
    }
    return false;
}

// Verifica si se ha ganado el juego
bool Board::checkWin() {
    return countRevealedSafeCells() == ((width * height) - numMine);
}
