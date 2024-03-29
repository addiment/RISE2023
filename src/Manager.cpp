#include <steam/steam_api.h>
#include "Manager.h"
#include "EzInputSys.h"
#include "EzSoundSys.h"
#include "misc.h"
#include <queue>

using namespace std;

bool Manager::isRunning = true;
SDL_Window* Manager::window = nullptr;
// SDL_GLContext context;
SDL_Renderer* Manager::renderer = nullptr;
Scene* Manager::currentScene = nullptr;
Scene* scheduledSceneChange = nullptr;
IVec2 windowSize = { 640, 640 };
[[maybe_unused]] IVec2 lastWindowedSize = { 640, 640 };
uint64_t lastTickStartTime = 0;
uint64_t gameTicksSinceSceneLoad = 0;

void Manager::changeScene(Scene* scene) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "MANAGER Changing to scene (%s)", (scene->getSceneName() ? scene->getSceneName() : "unnamed"));
    scheduledSceneChange = scene;
}

uint32_t isFullscreen() {
    uint32_t wflags = SDL_GetWindowFlags(Manager::window);
    return wflags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void onWindowResized(int nw, int nh) {
    windowSize = { nw, nh };
    if (!isFullscreen()) lastWindowedSize = windowSize;
}

int Manager::play(int argc, char* argv[], SceneFactory initialSceneFactory, const char* windowName) {

#ifdef CMAKE_BUILD_DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

    {
        int i = Manager::init(windowName);
        if (i) return i;
    }

    // handoff
    EnginePostInit();

    // SET THE INITIAL SCENE
    changeScene(initialSceneFactory());

    while (isRunning) {
        if (scheduledSceneChange) {
            if (currentScene) { // NOLINT(readability-delete-null-pointer) because we will actually do other stuff later
                // TODO: cleanup current scene
                // Stop all audio
//                SoundSystem::flush();
                delete currentScene;
            }
            gameTicksSinceSceneLoad = 0;
            currentScene = scheduledSceneChange;
            scheduledSceneChange = nullptr;
            currentScene->onPlay();
        }
        tick();
    }

    Manager::shutdown();

    return 0;
}

int Manager::init(const char* windowName) {
#pragma region Steam Init
#ifdef USE_STEAM
    if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid)) {
        return 1;
    }
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
#pragma endregion Steam Init

#pragma region SDL2 Init
    // Init SDL2
    {
        int res = SDL_Init(SDL_INIT_EVERYTHING);
        if (res < 0) {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
            return res;
        }
    }
#pragma endregion SDL2 Init

#pragma region SDL2_image Init
    // Init SDL2_image
    {
        int flags = IMG_INIT_PNG;
        int res = IMG_Init(flags);
        if (res != flags) {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_image: %s", IMG_GetError());
            return (res ? res : 1);
        }
    }
#pragma endregion SDL2_image Init

#pragma region SDL2_mixer Init
    // Init SDL2_image
    {
        int flags = MIX_INIT_MP3;
        int res = Mix_Init(flags);
        if (res != flags) {
            SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_mixer: %s", Mix_GetError());
            return (res ? res : 1);
        }
    }
#pragma endregion SDL2_mixer Init

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetSwapInterval(1);

#pragma region Create Window
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN /*| SDL_WINDOW_OPENGL*/ | SDL_WINDOW_RESIZABLE );
    if (window == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        return 1;
    }
#pragma endregion Create Window

#pragma region Create Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
        return 1;
    }
#pragma endregion Create Renderer

    SDL_Log("initialized");

    // Init input system
    InputSystem::init();

    {
        int res = SoundSystem::init();
        if (res) return res;
    }

    return 0;
}

void Manager::shutdown() {
    SDL_Log("shutting down");

    // TODO: run cleanup code

    IMG_Quit();
    Mix_Quit();
//    TTF_Quit();
    SDL_Quit();

#ifdef USE_STEAM
    SteamAPI_Shutdown();
#endif // USE_STEAM

    SDL_Log("goodnight");
}

void Manager::tick() {
    uint64_t tickTime = SDL_GetPerformanceCounter();
    double delta = (double)(tickTime - lastTickStartTime) / (double)SDL_GetPerformanceFrequency();
    printf("%f", delta);
    lastTickStartTime = tickTime;

#pragma region SDL_PollEvent
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_WINDOWEVENT:
                switch (ev.window.event) {
                    case SDL_WINDOWEVENT_RESIZED: onWindowResized(ev.window.data1, ev.window.data2); break;
                    // fallthrough if event is closing the window
                    case SDL_WINDOWEVENT_CLOSE: goto FALLTHROUGH_QUIT;
                    // no fallthrough for other events
                    default: goto FALLTHROUGH_BREAK;
                }
                // break the outer switch and poll the next event
                FALLTHROUGH_BREAK: break;
                // fallthrough into the SDL_QUIT case
                FALLTHROUGH_QUIT: continue;
            case SDL_QUIT: {
                isRunning = false;
                return;
            }
            case SDL_KEYDOWN:
                // key repeats are always inconsistent.
                if (ev.key.repeat) break;
            case SDL_KEYUP: {
                switch (ev.key.keysym.sym) {
                    case SDLK_f:
                    case SDLK_F11: {
                        if (ev.key.state == SDL_PRESSED) SDL_SetWindowFullscreen(Manager::window, (isFullscreen() ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP));
                        break;
                    }
                    default: break;
                }
            }
        }
    }
#pragma endregion SDL_PollEvent

#ifdef USE_STEAM
    SteamAPI_RunCallbacks();
#endif // USE_STEAM

    InputSystem::update();

    // Current Scene
    currentScene->update(delta);

    // Actors
    {
        // run onPlay() and update()
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

    // render all actors
    for (auto & actor : currentScene->actors) actor.second->render();

    SDL_RenderPresent(renderer);
//#ifdef CMAKE_BUILD_DEBUG
//    GLenum err = glGetError();
//    if (err != 0) SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%x %s", err, glewGetErrorString(err));
//#endif
    gameTicksSinceSceneLoad++;
}

IVec2 Manager::getWindowSize() {
    return windowSize;
}
