#include "engine.hpp"

//funcion para deInit borrar datos dinamicos 
//funciones para obtener las celdas del board desde EL engine

Engine::Engine() {
    // presentacion->Draw(scene, info)
}

void Engine::init(int width, int height) {
    board = Board(width, height);
    board.generateBoard();
}

void Engine::deInit(){
    //Elimanar datos de init
}

std::vector<std::vector<Cell>> Engine::getInformationCell() const {
    return board.getCells();
}

Engine::~Engine() {
}
