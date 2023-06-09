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

using SceneFactory = aLib::Function<Scene*>;

class Manager {
public:
    static bool isRunning;
    static SDL_Window* window;
    // SDL_GLContext context;
    static SDL_Renderer* renderer;

    // engine entry point
    // Internally, it calls init, shutdown, and tick.
    // It's also in charge of handling scene transitions (NOT in the changeScene or tick functions!)
    static int play(int argc, char* argv[], SceneFactory initialSceneFactory, const char* windowName);
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
    [[maybe_unused]] [[nodiscard]] RETURN_MAY_BE_NULL static inline Pawn* getActivePawn() {
        if (!currentScene) return nullptr;
        else return currentScene->activePawn;
    }
    static IVec2 getWindowSize();
private:
    Manager() = default;

    static Scene *currentScene;

    // Initializes all engine subsystems (i.e. SDL, Steam)
    static int init(const char* windowName);
    // Cleans up resources (mostly...)
    static void shutdown();
    // Runs every frame. Handles updating and rendering actors.
    static void tick();
};


#endif // TOOLKITENGINEV3_MANAGER_H
