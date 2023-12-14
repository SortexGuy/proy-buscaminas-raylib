#include "engine.hpp"
#include "storage/gamestatus.h"

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
    this->moves_played = 0;
    this->score = 0;
    this->cache_remaining_mines = 0;
    this->last_move_checked = 0;
    this->game_paused = false;
}

void Engine::registerPlayerMove(int x, int y, Cell cell_info) {
    setPlaying(true);
    if (!board.getCells().at(x).at(y).isVisible()) {
        moves_played++;
    }
    board.setCellInfo(x, y, cell_info);
}

void Engine ::setGamePaused(bool gamePaused) {
    this->game_paused = gamePaused;
}

bool Engine ::getGamePaused() {
    return game_paused;
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

void Engine::revealAdjacentCells(int x, int y) {
    // movesPlayed++; // no es necesario porque ya cambie la llamada del click
    // del medio
    board.revealAdjacentCells(x, y);
    board.revealAdjNotFlaggedCells(x, y);
}

void Engine::saveGame(std::string playerName) {
    data.save(playerName,score,timer,board.countMineAndFlag(),board.indicarDificulta());
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

int Engine::getRemainingMines() {
    if (last_move_checked != moves_played) {
        cache_remaining_mines = board.countMinesDiscovered();
        last_move_checked = moves_played;
    }
    return cache_remaining_mines;
}

int Engine::getMoves() {
    return moves_played;
}

std::vector<std::vector<Cell>> Engine::getCellInfo() const {
    return board.getCells();
}

void Engine::calcularPuntuaje() {
    score = ((board.countMineAndFlag() * 2.0) / moves_played / (timer / 60.0)) *
            100;
}

std::string Engine::getPlayerHighestScore(){
    return data.getPlayerWithHighestScore();
}



Engine::~Engine() {
}
