#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <string>
#include "archiving.hpp"

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
    Data getData();

   public:
    GameSaver();
    std::string getPlayerName();
    int getScore();
    float getTime();
    int getFoundMines();
    std::string getDifficulty();
    void save(std::string playerName,
              double score,
              int time,
              int foundMines,
              std::string difficulty);

    std::string getPlayerWithHighestScore();
};
#endif
