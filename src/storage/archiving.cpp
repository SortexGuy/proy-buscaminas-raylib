#include <fstream>
#include <iostream>
#include <string>

class FileManager {
   public:
    FileManager(const std::string& filename) {
        this->filename = filename;
    }

    bool updateFile(const std::string& content) {
        std::cout << filename << std::endl;
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo para escritura."
                      << std::endl;
            return false;
        }

        file << content;
        file.close();
        return true;
    }

    bool writeFile(const std::string& content) {
        std::string currentData = readFile();

        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo para escritura."
                      << std::endl;
            return false;
        }

        file << content;
        file << currentData;
        file.close();
        return true;
    }

    std::string readFile() {
        std::string content = "";
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo para lectura."
                      << std::endl;
            return "";
        }

        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }

        file.close();
        return content;
    }

   private:
    std::string filename;
};
