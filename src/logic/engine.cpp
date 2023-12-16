#include "engine.hpp"
#include <cmath>
#include "fmt/core.h"

// Constructor
Engine::Engine() {
}

// Constructor
void Engine::init(int width, int height, int numMine) {
    board = Board(width, height, numMine);
    board.generateBoard();
}

// Destruye el tablero
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

// Registra el movimiento de un jugador en el tablero de juego
void Engine::registerPlayerMove(int x, int y, Cell cell_info) {
    setPlaying(true);
    if (!board.getCells().at(x).at(y).isVisible()) {
        moves_played++;
    }
    // Establece la información de la celda en el tablero
    board.setCellInfo(x, y, cell_info);
}

// Establece el estado de pausa del juego
void Engine ::setGamePaused(bool gamePaused) {
    this->game_paused = gamePaused;
}

// Devuelve el estado de pausa del juego
bool Engine ::getGamePaused() {
    return game_paused;
}

// Devuelve si el juego ha terminado
bool Engine::isGameOver() {
    return board.checkGameOver();
}

// Devuelve si el jugador ha ganado
bool Engine::didPlayerWin() {
    return board.checkWin();
}

// Revela las celdas adyacentes a la celda especificada
void Engine::revealAdjacentCells(int x, int y) {
    board.revealAdjacentCells(x, y);
    board.revealAdjNotFlaggedCells(x, y);
}

// Guarda los datos del jugador
void Engine::saveGame(std::string playerName) {
    calculateScore();
    data.save(playerName, score, timer, board.countMineAndFlag(),
              board.indicateDifficulty());
}

// Actualiza el tiempo
void Engine::updateTimer(double deltaTime) {
    this->timer += deltaTime;
}

// Devuelve el tiempo
double Engine::getTime() {
    return this->timer;
}

// Establece el estado del jugador
void Engine::setPlaying(bool val) {
    this->playing = val;
}

// Devuelve el estado del jugador
bool Engine::isPlaying() {
    return this->playing;
}

// Devuelve el numero de minas restantes
int Engine::getRemainingMines() {
    if (last_move_checked != moves_played) {
        cache_remaining_mines = board.countMinesDiscovered();
        last_move_checked = moves_played;
    }
    return cache_remaining_mines;
}

// Devuelve el numero de jugadas
int Engine::getMoves() {
    return moves_played;
}

// Devuelve las celdas del tablero
std::vector<std::vector<Cell>> Engine::getCellInfo() const {
    return board.getCells();
}

// Calcula el puntaje
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

// Devuelve el puntaje del jugador con el mayor puntaje
Data Engine::getPlayerHighestScore() {
    return data.getPlayerWithHighestScore();
}

// Destructor
Engine::~Engine() {
}
