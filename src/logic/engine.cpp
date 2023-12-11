#include "engine.hpp"

Engine::Engine() {
    // presentacion->Draw(scene, info)
}

void Engine::init(int width, int height) {
    board = Board(width, height);
    board.generateBoard();
}

void Engine::deinit() {
    board.clear();
}

void Engine::registerPlayerMove(int x, int y, Cell cell_info) {
    // Registrar la jugada, sea cual sea la movida del jugador
    // actualizar la celda especificada con la nueva informacion
}

void Engine::revealAdjacentCells(int x, int y) {
    board.revealAdjNotFlaggedCells(x, y);
}

std::vector<std::vector<Cell>> Engine::getCellInfo() const {
    return board.getCells();
}

Engine::~Engine() {
}
