#include "archiving.hpp"
#include <cstring>
#include <string>
#include "fmt/core.h"
#include "raylib.h"

FileManager::FileManager(const std::string& filename) {
    this->filename = filename;
}

// bool FileManager::updateFile(const std::string& content) {
//     std::cout << filename << std::endl;
//     std::ofstream file(filename);
//
//     if (!file.is_open()) {
//         std::cout << "No se pudo abrir el archivo para escritura." <<
//         std::endl; return false;
//     }
//
//     file << content;
//     file.close();
//     return true;
// }

bool FileManager::writeFile(const std::string& content) {
    if (!DirectoryExists(GetDirectoryPath(filename.c_str()))) {
        fmt::println("No se pudo abrir el archivo para escritura.");
        return false;
    }

    std::string text(0, 0);
    if (FileExists(filename.c_str())) {
        // Si existe el archivo, cargar texto existente
        char* loaded_file = LoadFileText(filename.c_str());
        text = std::string(loaded_file);
        UnloadFileText(loaded_file);
    }

    text = content + text;
    char* currentData = new char[text.length() + 1];
    std::strcpy(currentData, text.c_str());
    SaveFileText(filename.c_str(), currentData);
    delete[] currentData;
    return true;
}

std::string FileManager::readFile() {
    if (!FileExists(filename.c_str())) {
        fmt::println("No se pudo abrir el archivo para lectura.");
        return "";
    }
    char* text = LoadFileText(filename.c_str());
    std::string content(text);
    return content;
}
