#pragma once
#ifndef TOOLKITENGINEV3_MANAGER_H
#define TOOLKITENGINEV3_MANAGER_H

#include <SDL2/SDL.h>
#include "tkev3.h"
#include "aecs.h"

#define USE_STEAM

int main(int argc, char* argv[]);

class Manager {
public:
    static bool isRunning;
    static SDL_Window* window;
//    static SDL_GLContext context;
    static SDL_Renderer* renderer;

    static int play(int argc, char* argv[]);
private:
    static int init();
    static void shutdown();
    static void tick();
};

#endif // TOOLKITENGINEV3_MANAGER_H
