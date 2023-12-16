#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <string>
#include "archiving.hpp"

/*Estructura para almacenar los datos del jugador*/
struct Data {
    std ::string namePlayer;
    double score;
    int time;
    int foundMines;
    std ::string difficulty;
};

class GameSaver {
   private:
    FileManager fileManager = FileManager("Puntuajes.txt");

    std::string structToString(const Data& data);
    Data stringToStruct(const std::string& String);
    Data getData();  // obtener datos del jugador

   public:
    GameSaver();
    // obtener los valores del jugador
    std::string getPlayerName();
    int getScore();
    float getTime();
    int getFoundMines();
    std::string getDifficulty();
    // guardar datos del jugador
    void save(std::string playerName,
              double score,
              int time,
              int foundMines,
              std::string difficulty);
    // obtener los datos del jugador con la puntuación más alta
    Data getPlayerWithHighestScore();
};
#endif
