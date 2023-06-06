#pragma once
#ifndef TOOLKITENGINEV3_MANAGER_H
#define TOOLKITENGINEV3_MANAGER_H

#include <SDL2/SDL.h>
#include "tkev3.h"
#include "aecs.h"

#define USE_STEAM

int main(int argc, char* argv[]);

class Manager;
// Singleton accessor
inline class Manager* Manager();

class Manager {
public:
    bool isRunning = true;
    SDL_Window* window = nullptr;
    // SDL_GLContext context;
    SDL_Renderer* renderer = nullptr;

    int play(int argc, char* argv[]);
private:
    friend inline class Manager* Manager() {
        static class Manager* global = nullptr;
        if (!global) global = new class Manager();
        return global;
    }
    Manager() = default;
    int init();
    void shutdown();
    void tick();
};


#endif // TOOLKITENGINEV3_MANAGER_H
