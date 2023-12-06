#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "ceils.h"


using namespace std;

class Board {

   public:
    Board(int widh, int height);
    ~Board();

    void generateBoard();
    void mostrarMinasTablero();
    void RevealCells(int x,int y );
    void ponerbandera();
    void quitarbandera();

   private:
    int id;
    int width;
    int height;
    vector<vector<Ceil>> ceils;

    void ponerMines();
    void RevealAdjacentCells( int x,int y );
    void CountAdjacentMines(int x,int y);
};


#endif // BOARD_H