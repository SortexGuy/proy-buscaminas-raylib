#include "saveArchive.h"
#include <fstream>
#include <iostream>
#include <string>

void SavedArchive::saveGame(const std::string& gameName, const std::string& gameStatus) {
    std::ofstream file(gameName);

    if (!file) {
        std::cout << "Error al guardar partida." << std::endl;
        return;
    }
    file << gameStatus;
    file.close();
}

void SavedArchive::loadGame(const string& gameName) {
    std::ifstream file(gameName);
    if (!file) {
        std::cout << "Error al cargar partida." << std::endl;
        return;
    }
    string line;
    while (std::getline(file, line)) {
        // Lógica para cargar los datos del juego
    }
    file.close();
    
    // estructura para representar el estado del juego
    struct GameStatus {
        string playerName; 
        int score; 
        float time; 
        int foundMines; 
        string difficulty; 
        GameStatus parse_saved_game(const string& gameLine) {
            GameStatus game;
    
            // Buscar las posiciones de los caracteres delimitadores
            size_t posPlayerName = gameLine.find("playerName");
            size_t posScore = gameLine.find("score");
            size_t posTime = gameLine.find("time");
            size_t posFoundMines = gameLine.find("foundMines");
            size_t posDifficulty = gameLine.find("difficulty");


            // Extraer los valores de los campos correspondientes
            string s_playerName = gameLine.substr(posPlayerName + 11, posScore - posPlayerName - 11);
            string s_score = gameLine.substr(posScore + 6, posTime - posScore - 6);
            string s_time = gameLine.substr(posTime + 4, posFoundMines - posTime - 4);
            string s_foundMines = gameLine.substr(posFoundMines + 12, posDifficulty - posFoundMines - 12);
            string s_difficulty = gameLine.substr(posDifficulty + 11);

            // Convertir los valores a los tipos correspondientes
            game.playerName = s_playerName;
            game.score = stoi(s_score);
            game.time = stof(s_time);
            game.foundMines = stoi(s_foundMines);
            game.difficulty = s_difficulty;

            return game;
            
        }
    };
}
