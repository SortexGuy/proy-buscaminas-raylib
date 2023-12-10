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
bool Cell ::getIsMine() {
    return isMine;
}

void Cell ::setFlag(bool flag) {
    this->flag = flag;
}
bool Cell ::getFlag() {
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
