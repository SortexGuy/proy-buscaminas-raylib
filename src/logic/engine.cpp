#include "engine.hpp"

Engine::Engine() {
    // presentacion->Draw(scene, info)
}

void Engine::init(int width, int height) {
    board = Board(width, height);
    board.generateBoard();
}

void Engine::deInit() {
    // Elimanar datos de init
}

std::vector<std::vector<Cell>> Engine::getCellInfo() const {
    return board.getCells();
}

Engine::~Engine() {
}
