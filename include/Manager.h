#pragma once
#ifndef TOOLKITENGINEV3_MANAGER_H
#define TOOLKITENGINEV3_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Scene.h"

// forward decls.
class Camera;

// DEFINE THIS IN YOUR MAIN.CPP
void EnginePostInit();

class Manager {
public:
    static bool isRunning;
    static SDL_Window* window;
    // SDL_GLContext context;
    static SDL_Renderer* renderer;

    // engine entry point
    static int play(int argc, char* argv[], Scene* initialScene);
    // returns the current scene
    [[nodiscard]] static inline Scene *getScene() { return currentScene; }
    // changes the scene
    static void changeScene(Scene *scene);
    // calls the function of the same name on the current scene
    [[nodiscard]] RETURN_MAY_BE_NULL static inline Camera* getActiveCamera() {
        if (!currentScene) return nullptr;
        else return currentScene->activeCamera;
    }
    // calls the function of the same name on the current scene
    [[nodiscard]] RETURN_MAY_BE_NULL static inline Pawn* getActivePawn() {
        if (!currentScene) return nullptr;
        else return currentScene->activePawn;
    }
private:
    Manager() = default;

    static Scene *currentScene;

    static int init();
    static void shutdown();
    static void tick();
};


#endif // TOOLKITENGINEV3_MANAGER_H
