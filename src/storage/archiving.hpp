#ifndef ARCHIVING_H
#define ARCHIVING_H
#include <string>

class FileManager {
   public:
    FileManager(const std::string& filename);  // inicializa la clase con un
                                               // nombre de archivo dado.
    bool writeFile(
        const std::string&
            content);  // escribir el contenido proporcionado en el archivo
                       // especificado por el nombre de archivo.
    std::string readFile();  // lee y devuelve el contenido del archivo
                             // especificado por el nombre de archivo.

   private:
    std::string filename;  // nombre de archivo
};
#endif  // !ARCHIVING_H
