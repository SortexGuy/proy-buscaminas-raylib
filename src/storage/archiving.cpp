#include "archiving.hpp"
#include <string>
#include "fmt/core.h"
#include "raylib.h"

// Constructor de FileManager
FileManager::FileManager(const std::string& filename) {
    this->filename = filename;
}

// Función para escribir en el archivo
bool FileManager::writeFile(const std::string& content) {
    if (!DirectoryExists(GetDirectoryPath(filename.c_str()))) {
        fmt::println(
            "No se pudo abrir el archivo para escritura.");  // Directorio
                                                             // inexistente,
                                                             // muestra un
                                                             // mensaje de error
        return false;
    }

    std::string text(0, 0);
    if (FileExists(filename.c_str())) {
        // Si el archivo existe, cargar el texto
        char* loaded_file = LoadFileText(filename.c_str());
        text = std::string(loaded_file);
        UnloadFileText(loaded_file);
    }

    text = content + text;
    char* currentData = new char[text.length() + 1];
    std::strcpy(currentData,
                text.c_str());  // Copia el contenido al puntero de caracteres
    SaveFileText(filename.c_str(), currentData);
    delete[] currentData;  // Libera la memoria del puntero de caracteres
    return true;
}

/*Escribe el contenido proporcionado en un archivo.
@param content el contenido a escribir en el archivo
@return true si la operación de escritura fue exitosa, false en caso contrario
*/

// Función para leer el contenido del archivo
std::string FileManager::readFile() {
    if (!FileExists(filename.c_str())) {
        fmt::println(
            "No se pudo abrir el archivo para lectura.");  // Archivo
                                                           // inexistente,
                                                           // muestra un mensaje
                                                           // de error
        return "";
    }
    char* text = LoadFileText(filename.c_str());  // Cargar el texto del archivo
    std::string content(
        text);  // Convierte el texto en una cadena de caracteres
    return content;
}

/*Lee el contenido de un archivo y lo devuelve como una cadena de texto.
@return El contenido del archivo como una cadena de texto.
@throws FileNotFoundError Si el archivo no existe.*/
