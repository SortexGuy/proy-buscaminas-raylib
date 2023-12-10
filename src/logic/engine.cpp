#include "engine.hpp"

Engine::Engine() {
    // presentacion->Draw(scene, info)
}

void Engine::init(int width, int height) {
    Board board = Board(width, height);

    board.generateBoard();
}

<<<<<<< HEAD
=======
void Engine::deInit(){
    //Elimanar datos de init
}

std::vector<std::vector<Cell>> Engine::getCellInfo () const {
    return board.getCells();
}

>>>>>>> 5effc87a3803778025386025e94ff32b0efff994
Engine::~Engine() {
}
