#include "ceils.h"

void Ceil:: setIsVisible(bool isVisible ){
    this-> isVisible = isVisible;
}
bool Ceil :: getIsVisible (){
    return isVisible;
} 

void Ceil :: setIsMine(bool isMine){
    this->isMine = isMine;
}
bool Ceil ::getIsMine( ){
    return isMine;
}


void Ceil ::setFlag( bool flag ){
    this->flag = flag;
}
bool Ceil :: getFlag( ){
    return flag;
}

void Ceil ::setValue( int value ){
    this->value = value;
}
int Ceil ::getValue( ){
    return value;
}

/*void Ceil::RevealAdjacentCells(int currentX,int currentY ) {

    isVisible = true;

    int newx =0;
    int newy =0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            newx = currentX + i ;
            newy = currentY + j ;
            //acceder a otra celda
            // si value == 0 recursividad 
            RevealAdjacentCells(newx,newy);
        }
    }
}

void Ceil::CountAdjacentMines(int currentX,int currentY ) {

    if (isMine) {
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

            newx = currentX + i ;
            newy = currentY + j ;

            //verificar si la celda adyacentes esta en los limites
            //acceder a otra celda
            //verificar si es una bomba
            
            mineCount++;
        }

    }

    value = mineCount;


}

void Ceil::Reveal(int currentX,int currentY ) {

    isVisible = true;

    if (!isMine) {
        if (value == 0) {
            RevealAdjacentCells(currentX,currentY );
        }
        //game over o algo
    }
}*/

Ceil::Ceil(){
}

Ceil::~Ceil() {
}