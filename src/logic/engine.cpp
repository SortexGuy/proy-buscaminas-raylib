#include "engine.hpp"
#include "raylib.h"

// funcion para cambiar el estado de la bandera

Engine::Engine() {
}

void Engine::init(int width, int height, int numMine) {
    board = Board(width, height, numMine);
    board.generateBoard();
}

void Engine::deinit() {
    this->board.clear();
    this->timer = 0;
    this->playing = false;
    this->movesPlayed = 0;
}

bool Engine::registerPlayerMove(int x, int y, Cell cell_info) {
    board.setCellInfo(x, y, cell_info);
    movesPlayed++;
    return isGameOver();  // Game over??
}

void Engine ::setGamePaused(bool gamePaused) {
    this->gamePaused = gamePaused;
}

bool Engine ::getGamePaused() {
    return gamePaused;
}

bool Engine::isGameOver() {
    return board.checkGameOver();
}

bool Engine::didPlayerWin() {
    return board.checkWin();
    /*int revealedSafeCells = board.countRevealedSafeCells();
    return revealedSafeCells == ((board.boardSize())-
    board.countMinesBoard()cambiar por numMine);*/
}

bool Engine::revealAdjacentCells(int x, int y) {

    movesPlayed++;
    board.revealAdjacentCells(x, y);
    board.revealAdjNotFlaggedCells(x, y);

    return isGameOver();  // Game over??
}

void Engine::saveGame(std::string playerName) {

    //GameStatus date = GameStatus(playerName,score,timer,board.countMinesBoard(),board.indicarDificulta());

}  // Se necesita implementar

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

int Engine::getMines() {
    return board.countMinesBoard();
}
int Engine::getMoves() {
    return movesPlayed;
}

std::vector<std::vector<Cell>> Engine::getCellInfo() const {
    return board.getCells();
}

void Engine::calcularPuntuaje(){
    score = ((board.countMineAndFlag()*2)/movesPlayed/(timer/60.0f))*100;
}

string Engine::dificulta(){

}

Engine::~Engine() {
}
