#include "cells.h"

void Cell::setIsVisible(bool isVisible) {
    this->isVisible = isVisible;
}
bool Cell ::getIsVisible() {
    return isVisible;
}

void Cell ::setIsMine(bool isMine) {
    this->isMine = isMine;
}
bool Cell ::isMined() {
    return isMine;
}

void Cell ::setFlag(bool flag) {
    this->flag = flag;
}
bool Cell ::isFlagged() {
    return flag;
}

void Cell ::setValue(int value) {
    this->value = value;
}
int Cell ::getValue() {
    return value;
}

Cell::Cell() {
}

Cell::~Cell() {
}
