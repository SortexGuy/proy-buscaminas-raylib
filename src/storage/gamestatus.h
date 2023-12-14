#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <string>
#include "raylib.h"

class GameStatus {
   private:
    std::string playerName;
    int score;
    float time;
    int foundMines;
    std::string difficulty;

   public:
    GameStatus(){};
    GameStatus(std::string playerName,
               int score,
               float time,
               int foundMines,
               std::string difficulty) {
        this->playerName = playerName;
        this->score = score;
        this->time = time;
        this->foundMines = foundMines;
        this->difficulty = difficulty;
    }
    void setPlayerName(std::string playerName) {
        this->playerName = playerName;
    }
    std::string getPlayerName() {
        return playerName;
    }
    void setScore(int score) {
        this->score = score;
    }
    int getScore() {
        return score;
    }
    void setTime(float time) {
        this->time = time;
    }
    float getTime() {
        return time;
    }
    void setFoundMines(int foundMines) {
        this->foundMines = foundMines;
    }
    int getFoundMines() {
        return foundMines;
    }
    void setDifficulty(std::string difficulty) {
        this->difficulty = difficulty;
    }
    std::string getDifficulty() {
        return difficulty;
    }

    GameStatus parse_saved_game(const std::string& gameLine) {
        GameStatus game;

        // Buscar las posiciones de los caracteres delimitadores
        size_t posPlayerName = gameLine.find("playerName");
        size_t posScore = gameLine.find("score");
        size_t posTime = gameLine.find("time");
        size_t posFoundMines = gameLine.find("foundMines");
        size_t posDifficulty = gameLine.find("difficulty");

        // Extraer los valores de las posiciones
        std::string s_playerName =
            gameLine.substr(posPlayerName + 12, posScore - posPlayerName - 13);
        int s_score =
            std::stoi(gameLine.substr(posScore + 6, posTime - posScore - 7));
        float s_time = std::stof(
            gameLine.substr(posTime + 5, posFoundMines - posTime - 6));
        int s_foundMines = std::stoi(gameLine.substr(
            posFoundMines + 11, posDifficulty - posFoundMines - 12));
        std::string s_difficulty = gameLine.substr(posDifficulty + 11);

        // Convertir los valores a los tipos correspondientes
        game.setPlayerName(s_playerName);
        game.setScore(s_score);
        game.setTime(s_time);
        game.setFoundMines(s_foundMines);
        game.setDifficulty(s_difficulty);

        return game;
    }
};

#endif