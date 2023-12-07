#include "saveArchive.h"

void SavedArchive::saveGame(const string& gameName, const string& gameStatus) {
    std::ofstream file(gameName);

    if (!file.is_open()) {
        std::cout << "Error al guardar partida." << std::endl;
        return;
    }

    file << gameStatus;
    file.close();
}

void SavedArchive::loadGame(const string& gameName) {
    std::ifstream file(gameName);

    if(!file) {
        std::cout << "Error al cargar partida." << std::endl;
        return;
    }

    string line;
    while (std::getline(file, line)) {
        //Cargar Datos del juego
    }

    file.close();
}