#include "cells.h"

void Cell::setVisible(bool visible) {
    this->visible = visible;
}
bool Cell::isVisible() {
    return visible;
}

void Cell::setMined(bool isMine) {
    this->isMine = isMine;
}
bool Cell::isMined() {
    return isMine;
}

void Cell::setFlag(bool flag) {
    this->flag = flag;
}
bool Cell::isFlagged() {
    return flag;
}

void Cell::setValue(int value) {
    this->value = value;
}
int Cell::getValue() {
    return value;
}

void Cell::toggleFlag() {
    this->flag = !this->flag;
}

Cell::Cell() {
}

Cell::~Cell() {
}
