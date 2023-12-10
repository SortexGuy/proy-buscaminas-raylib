#include "engine.hpp"

Engine::Engine() {
    // presentacion->Draw(scene, info)
}

void Engine::init(int width, int height) {
    Board board = Board(width, height);

    board.generateBoard();
}

Engine::~Engine() {
}
