#ifndef SAVEARCHIVE_H 
#define SAVEARCHIVE_H

#include <iostream>
#include <fstream>

using std::string;

class SaveArchive {
public:   
    void saveGame(const string& gameName, const string& gameStatus);
    void loadGame(const string& gameName); 
};

#endif //SAVEARCHIVE_H