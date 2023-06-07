#pragma once
#ifndef TOOLKITENGINEV3_MANAGER_H
#define TOOLKITENGINEV3_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "aces.h"
#include "tkev3.h"
#include "Scene.h"

#define USE_STEAM

class Manager {
public:
    static bool isRunning;
    static SDL_Window* window;
    // SDL_GLContext context;
    static SDL_Renderer* renderer;

    static int play(int argc, char* argv[], Scene* scene);
    [[nodiscard]] static Scene *getScene();
    static void changeScene(Scene *scene);
private:
    Manager() = default;
    static Scene *currentScene;
    static int init();
    static void shutdown();
    static void tick();
};


#endif // TOOLKITENGINEV3_MANAGER_H
