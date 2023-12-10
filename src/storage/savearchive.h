#ifndef SAVEARCHIVE_H
#define SAVEARCHIVE_H

#include <fstream>
#include <iostream>

using std::string;

class SavedArchive {
   public:
    void saveGame(const string& gameName, const string& gameStatus);
    void loadGame(const string& gameName);
};

#endif