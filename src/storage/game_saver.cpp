#include "game_saver.hpp"  // Incluye el archivo de encabezado "game_saver.hpp"
#include <iostream>  // Incluye la biblioteca iostream para entrada y salida estándar
#include <sstream>  // Incluye la biblioteca sstream para manipulación de cadenas
#include <string>  // Incluye la biblioteca string para trabajar con cadenas de caracteres
#include "archiving.hpp"  // Incluye el archivo de encabezado "archiving.hpp"
#include "fmt/core.h"     // Incluye la biblioteca fmt para formateo de texto

// Función para convertir una estructura Data en una cadena de texto
std::string GameSaver::structToString(const Data& data) {
    std::string result =
        fmt::format("{},{},{},{},{}\n", data.namePlayer, data.score, data.time,
                    data.foundMines, data.difficulty);
    return result;
}

// Función para convertir una cadena de texto en una estructura Data
Data GameSaver::stringToStruct(const std::string& String) {
    Data data;
    std::istringstream iss(String);
    std::getline(iss, data.namePlayer, ',');
    iss >> data.score;
    iss.ignore();  // Ignorar la coma
    iss >> data.time;
    iss.ignore();  // Ignorar el espacio en blanco
    iss >> data.foundMines;
    iss.ignore();  // Ignorar el espacio en blanco
    iss >> data.difficulty;
    return data;
}

// Función para obtener los datos del jugador
Data GameSaver::getData() {
    std::string String =
        fileManager.readFile();  // Lee el contenido del archivo
    return stringToStruct(
        String);  // Convierte la cadena en una estructura Data
}

// Constructor de GameSaver
GameSaver::GameSaver() {
}

// Función para obtener el nombre del jugador
std::string GameSaver::getPlayerName() {
    return getData()
        .namePlayer;  // Obtiene el nombre del jugador desde los datos
}

// Función para obtener la puntuación del jugador
int GameSaver::getScore() {
    return getData().score;  // Obtiene la puntuación desde los datos
}

// Función para obtener el tiempo del jugador
float GameSaver::getTime() {
    return getData().time;  // Obtiene el tiempo desde los datos
}

// Función para obtener el número de minas encontradas por el jugador
int GameSaver::getFoundMines() {
    return getData().foundMines;  // Obtiene el número de minas desde los datos
}

// Función para obtener la dificultad del juego del jugador
std::string GameSaver::getDifficulty() {
    return getData().difficulty;  // Obtiene la dificultad desde los datos
}

// Función para guardar los datos del jugador en el archivo
void GameSaver::save(std::string playerName,
                     double score,
                     int time,
                     int foundMines,
                     std::string difficulty) {
    Data data = {
        playerName, score, time, foundMines,
        difficulty};  // Crea una estructura Data con los datos proporcionados
    std::string dataString = structToString(
        data);  // Convierte la estructura Data en una cadena de texto

    fileManager.writeFile(
        dataString);  // Escribe la cadena de texto en el archivo
}

// Función para obtener los datos del jugador con la puntuación más alta
Data GameSaver::getPlayerWithHighestScore() {
    std::string fileContent =
        fileManager.readFile();  // Lee el contenido del archivo
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

    return highestScorePlayer;  // Devuelve los datos del jugador con la
                                // puntuación más alta
}
