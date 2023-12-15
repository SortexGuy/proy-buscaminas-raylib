#ifndef ARCHIVING_H
#define ARCHIVING_H
#include <string>

class FileManager {
   public:
    FileManager(const std::string& filename);
    // bool updateFile(const std::string& content);
    bool writeFile(const std::string& content);
    std::string readFile();

   private:
    std::string filename;
};
#endif  // !ARCHIVING_H
