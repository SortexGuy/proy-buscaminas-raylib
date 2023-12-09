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
}
