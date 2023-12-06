
#ifndef ENGINE_H
#define ENGINE_H

#include "raylib.h"
#include "raymath.h"
//#include "board.cpp"

class Engine {
   public:
    Engine();
    ~Engine();

    int scene = 0; //0: menu principal; 1:Pantalla de juego 

    void init ();

   private:
};

Engine::Engine() {
   //presentacion->Draw(scene, info)

}

void Engine::init(){
}


Engine::~Engine() {
}



#endif // ENGINE_H