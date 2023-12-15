#include "game_saver.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "archiving.hpp"
#include "fmt/core.h"

std::string GameSaver::structToString(const Data& data) {
    std::string result =
        fmt::format("{},{},{},{},{}\n", data.namePlayer, data.score, data.time,
                    data.foundMines, data.difficulty);
    return result;
}

Data GameSaver::stringToStruct(const std::string& String) {
    Data data;
    std::istringstream iss(String);
    std::getline(iss, data.namePlayer, ',');
    iss >> data.score;
    iss.ignore();  // Ignorar la coma
    iss >> data.time;
    iss.ignore();  //
    iss >> data.foundMines;
    iss.ignore();  //
    iss >> data.difficulty;
    return data;
}

Data GameSaver::getData() {
    std::string String = fileManager.readFile();
    return stringToStruct(String);
}

GameSaver::GameSaver() {
}

std::string GameSaver::getPlayerName() {
    return getData().namePlayer;
}

int GameSaver::getScore() {
    return getData().score;
}

float GameSaver::getTime() {
    return getData().time;
}

int GameSaver::getFoundMines() {
    return getData().foundMines;
}

std::string GameSaver::getDifficulty() {
    return getData().difficulty;
}

void GameSaver::save(std::string playerName,
                     double score,
                     int time,
                     int foundMines,
                     std::string difficulty) {
    Data data = {playerName, score, time, foundMines, difficulty};
    std ::string dataString = structToString(data);

    fileManager.writeFile(dataString);
}

Data GameSaver::getPlayerWithHighestScore() {
    std::string fileContent = fileManager.readFile();
    std::istringstream iss(fileContent);

    Data highestScorePlayer;
    highestScorePlayer.score = -1;  // Inicializa con un puntaje mínimo

    std::string line;

    while (std::getline(iss, line)) {
        Data playerData =
            stringToStruct(line);  // Convierte cada línea en estructura Data
        if (playerData.score > highestScorePlayer.score) {
            highestScorePlayer =
                playerData;  // Actualiza el jugador con el mayor puntaje
        }
    }

    return highestScorePlayer;
}
