#include "engine.hpp"
#include "raylib.h"

// funcion para cambiar el estado de la bandera

Engine::Engine() {
    // presentacion->Draw(scene, info)
}

void Engine::init(int width, int height/*int numMine*/) {
    board = Board(width, height/*numMine*/);
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

    board.setCellInfo(x, y, cell_info);
    movesPlayed++;
    return isGameOver();  // Game over??
}

void Engine :: setGamePaused(bool gamePaused){
    this->gamePaused = gamePaused;
}

bool Engine :: getGamePaused(){
    return gamePaused;
}

bool Engine:: isGameOver(){
    return board.checkGameOver();
}

bool Engine:: didPlayerWin() {
    int revealedSafeCells = board.countRevealedSafeCells();
    return revealedSafeCells == ((board.boardSize())- board.countMinesBoard()/*cambiar por numMine*/);
}

bool Engine::revealAdjacentCells(int x, int y) {

    board.revealAdjacentCells(x,y);
    board.revealAdjNotFlaggedCells(x, y);
    
    return isGameOver();  // Game over??
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
