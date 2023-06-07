#include <steam/steam_api.h>
#include "Manager.h"
#include "EzInputSys.h"
#include <queue>

using namespace std;

bool Manager::isRunning = true;
SDL_Window* Manager::window = nullptr;
// SDL_GLContext context;
SDL_Renderer* Manager::renderer = nullptr;
Scene* Manager::currentScene = nullptr;
Scene* scheduledSceneChange = nullptr;

void Manager::changeScene(Scene* scene) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "MANAGER Changing to scene (%s)", (scene->getSceneName() ? scene->getSceneName() : "unnamed"));
    scheduledSceneChange = scene;
}

int Manager::play(int argc, char* argv[], Scene* initialScene) {

#ifdef CMAKE_BUILD_DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

    {
        int i = Manager::init();
        if (i) return i;
    }

    // SET THE INITIAL SCENE
    changeScene(initialScene);

    while (isRunning) {
        if (scheduledSceneChange) {
            if (currentScene) {
                // TODO: cleanup current scene
                delete currentScene;
            }
            currentScene = scheduledSceneChange;
            scheduledSceneChange = nullptr;
            currentScene->onPlay();
        }
        tick();
    }

    Manager::shutdown();

    return 0;
}

int Manager::init() {

#ifdef USE_STEAM
    // Initialize Steam API
    if (!SteamAPI_Init()) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize Steam API!");
        return 1;
    }
    // Initialize Steam Input
    if (!SteamInput()->Init(false)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_INPUT, "Failed to initialize Steam Input!");
        return 1;
    }
#endif // USE_STEAM

    SizeVec2 windowSize = { 640, 640 };

    {
        int res = SDL_Init(SDL_INIT_EVERYTHING);
        if (res < 0) {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
            return res;
        }
    }

    {
        int flags = IMG_INIT_PNG;
        int res = IMG_Init(flags);
        if (res != flags) {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_image: %s", SDL_GetError());
            return (res ? res : 1);
        }
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetSwapInterval(1);

    window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)windowSize.w, (int)windowSize.h, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
        return 1;
    }

    SDL_Log("initialized");

    InputSystem::init();

    return 0;
}

void Manager::shutdown() {
    SDL_Log("shutting down");

    // TODO: run cleanup code

    SDL_Quit();

#ifdef USE_STEAM
    SteamAPI_Shutdown();
#endif // USE_STEAM
    SDL_Log("goodnight");
}

void Manager::tick() {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_WINDOWEVENT:
                // fallthrough if event is closing the window
                if (ev.window.event != SDL_WINDOWEVENT_CLOSE) { break; }
            case SDL_QUIT: {
                isRunning = false;
                return;
                break;
            }
//            case SDL_JOYAXISMOTION: {
//                ev.caxis.
//            }
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP: {
                const char* buttonName = SDL_GameControllerGetStringForButton((SDL_GameControllerButton)ev.cbutton.button);
                printf("Button %s %s\n", buttonName, (ev.cbutton.state ? "DOWN" : "UP"));
                break;
            }
        }
    }

    double delta = 0.01666666666666666666666666666;

#ifdef USE_STEAM
    SteamAPI_RunCallbacks();
#endif // USE_STEAM

    InputSystem::update();
//    InputSystem::ActionSet actionSet = InputSystem::getCurrentActionSet();
//    if (currentScene->activePawn) {
//        for (size_t i = 0; i < (size_t)InputSystem::DigitalAction::NumActions; i++) {
//            currentScene->activePawn->sendInput(actionSet, (InputSystem::DigitalAction)i, InputSystem::getDigitalActionValue((InputSystem::DigitalAction)i));
//        }
//        for (size_t i = 0; i < (size_t)InputSystem::AnalogAction::NumActions; i++) {
//            currentScene->activePawn->sendInput(actionSet, (InputSystem::AnalogAction)i, InputSystem::getAnalogActionValue((InputSystem::AnalogAction)i));
//        }
//    }

    // Current Scene
    currentScene->update(delta);

    // Actors
    {
        {
            for (auto & it : currentScene->actors) {
                if (!it.second->hasRunPlay) {
                    // onPlay is on the same frame as update and render
                    it.second->onPlay();
                    it.second->hasRunPlay = true;
                }
                it.second->update(delta);
            }
        }
        // cleanup
        {
            queue<Actor*> markeds{};
            for (auto & it : currentScene->actors)
                if (it.second->isMarkedForDeath()) markeds.push(it.second);

            using ID = Actor::ID;
            while (!markeds.empty()) {
                Actor *e = markeds.front();
                ID aid = e->id;
                currentScene->actors.erase(aid);
                ID m = currentScene->actors.rbegin()->first;
                if (m < aid) {
                    // at the end of the map, not fragmented
                    // retroactively clean up fragments (this is why fragments is a deque, not a queue)
                    while (m < currentScene->fragments.back()) currentScene->fragments.pop_back();
                } else {
                    currentScene->fragments.push_back(aid);
                }
                delete e;
                markeds.pop();
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0.f, 0.f, 0.f, 0.f);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (auto & actor : currentScene->actors) {
        actor.second->render();
    }

    SDL_RenderPresent(renderer);
//#ifdef CMAKE_BUILD_DEBUG
//    GLenum err = glGetError();
//    if (err != 0) SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%x %s", err, glewGetErrorString(err));
//#endif
}