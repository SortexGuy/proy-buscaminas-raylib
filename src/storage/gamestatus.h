#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <iostream>
#include <sstream>
#include <string>
#include "archiving.cpp"

struct Data{
    std :: string namePlayer;
    double score;
    int time;
    int foundMines;
    std :: string difficulty;
};

class GameStatus {

   private:
        FileManager fileManager = FileManager("Datos de los jugadores.txt");


    std::string structToString(const Data& data) {
        std::ostringstream oss;
        oss << data.namePlayer << ',' << data.score << ',' << data.time << ',' << data.foundMines << ','
        << data.difficulty << std::endl;
        return oss.str();
    }

    Data stringToStruct(const std::string& String) {
        Data data;
        std::istringstream iss(String);
        std::getline(iss, data.namePlayer, ',');
        iss >> data.score;
        iss.ignore(); // Ignorar la coma
        iss >> data.time;
        iss.ignore(); // 
        iss >> data.foundMines;
        iss.ignore(); // 
        iss >> data.difficulty;
        return data;
    }

   public:

    GameStatus(){
    }

    std::string getPlayerName() {
        return getData().namePlayer;
    }

    int getScore() {
        return getData().score;
    }

    float getTime() {
        return getData().time;
    }

    int getFoundMines() {
        return getData().foundMines;
    }

    std::string getDifficulty() {
        return getData().difficulty;
    }
   

    void save(std::string playerName, double score,int time,int foundMines,std::string difficulty){
        Data data = {playerName,score,time,foundMines,difficulty};
        std :: string dataString = structToString(data);

        fileManager.writeFile(dataString);
    }

    Data getData(){
        std:: string String = fileManager.readFile();
        return stringToStruct(String);
    }
   
};

#endif