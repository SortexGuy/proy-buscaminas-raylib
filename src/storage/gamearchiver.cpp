#include "gamearchiver.h"
#include "gamestatus.h"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <string>

void GameArchiver::saveFile(const std::string& fileName,
                            const std::string& gameStatus) {
    std::ofstream file(fileName);

    if (!file) {
        std::cout << "Error al guardar partida." << std::endl;
        return;
    }
    file << gameStatus;
    file.close();
}

void GameArchiver::loadFile(const string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cout << "Error al cargar partida." << std::endl;
        return;
    }

    string line;
    while (std::getline(file, line)){
        // Lógica para cargar los datos del juego
        // GameStatus loadedGame = parse_saved_game(line);
    }
    file.close();
}
