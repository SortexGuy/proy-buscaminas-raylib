#include "engine.hpp"
#include <cmath>
#include "fmt/core.h"

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
}

void Engine::revealAdjacentCells(int x, int y) {
    board.revealAdjacentCells(x, y);
    board.revealAdjNotFlaggedCells(x, y);
}

void Engine::saveGame(std::string playerName) {
    calculateScore();
    data.save(playerName, score, timer, board.countMineAndFlag(),
              board.indicateDifficulty());
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

void Engine::calculateScore() {
    std::string dif = board.indicateDifficulty();
    float val_dif = 1.0f;
    if (dif == "Media") {
        val_dif = 1.5f;
    } else if (dif == "Dificil") {
        val_dif = 1.7f;
    }

    if (timer < 0.1) {
        score = 0;
        return;
    }

    double mines_by_moves =
        (0.1 + board.countMineAndFlag() * 2.0) / moves_played;
    double timer_contribution = ((timer / 60.0) / val_dif);
    score = ((mines_by_moves * val_dif * 1.5) / timer_contribution) * 100;
    fmt::println("Score {}", score);
    score = floor(score);
}

Data Engine::getPlayerHighestScore() {
    return data.getPlayerWithHighestScore();
}

Engine::~Engine() {
}
