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

Ceil::Ceil(){
}

Ceil::~Ceil() {
}