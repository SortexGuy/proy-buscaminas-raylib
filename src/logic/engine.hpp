#ifndef ENGINE_H
#define ENGINE_H

#include "board.h"
#include "raylib.h"
#include "raymath.h"

class Engine {
   public:
    Engine();
    ~Engine();

<<<<<<< HEAD
    // int scene = 0;  // 0: menu principal; 1:Pantalla de juego
    void init(int width, int height);
=======
   // int scene = 0;  // 0: menu principal; 1:Pantalla de juego
   void init(int width, int height);
   void deInit();
   std::vector<std::vector<Cell>> getCellInfo() const;

>>>>>>> 5effc87a3803778025386025e94ff32b0efff994

   private:
};

#endif  // ENGINE_H
