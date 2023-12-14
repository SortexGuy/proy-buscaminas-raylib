#ifndef GAMEARCHIVER_H
#define GAMEARCHIVER_H
#include "raylib.h"
#include <fstream>
#include <iostream>

using std::string;

class GameArchiver {
   public:
    void saveFile(const string& gameName, const string& gameStatus);
    void loadFile(const string& gameName);
    string getFilePath (const string& gameName);
};

#endif