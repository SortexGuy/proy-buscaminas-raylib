#include "engine.hpp"
#include "raylib.h"

//funcion para cambiar el estado de la bandera 

Engine::Engine() {
    // presentacion->Draw(scene, info)
}

void Engine::init(int width, int height) {
    board = Board(width, height);
    board.generateBoard();
}

void Engine::deinit() {
    this->board.clear();
    this->timer = 0;
    this->playing = false;
    this->movesPlayed = 0;
}

bool Engine::registerPlayerMove(int x, int y, Cell cell_info) {
    // Registrar la jugada, sea cual sea la movida del jugador
    // actualizar la celda especificada con la nueva informacion
    return false;  // Game over??
}

bool Engine::revealAdjacentCells(int x, int y) {
    board.revealAdjNotFlaggedCells(x, y);
    return false;  // Game over??
}

void Engine::updateTimer(double deltaTime) {
    this->timer += deltaTime;
}

double Engine::getTime() {
    return this->timer;
}

void Engine::setPlaying(bool val) {
    this->playing = val;
}

bool Engine::isPlaying() {
    return this->playing;
}

std::vector<std::vector<Cell>> Engine::getCellInfo() const {
    return board.getCells();
}

Engine::~Engine() {
}
