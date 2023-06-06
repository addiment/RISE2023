#include <steam/steam_api.h>
#include "Manager.h"
#include "EzInputSys.h"
#include <queue>

using namespace std;

int Manager::play(int argc, char* argv[]) {

#ifdef NDEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

    {
        int i = Manager::init();
        if (i) return i;
    }

    while (isRunning) tick();

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetSwapInterval(1);

    window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)windowSize.w, (int)windowSize.h, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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

    InputSystem()->init();

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
//    //Check for joysticks
//    if (SDL_NumJoysticks() > 0) {
//        //Load joystick
//        if (SDL_IsGameController(0)) {
//            InputSystem::currentController = SDL_GameControllerOpen(0);
//            if (InputSystem::currentController == nullptr) {
//                SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Failed to open game controller @ index 0: %s", SDL_GetError());
//            }
//        }
//    }

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

#ifdef USE_STEAM
    SteamAPI_RunCallbacks();
#endif // USE_STEAM

    InputSystem()->update();

    // Actors
    {
        {

        }
        // cleanup
        {
            queue<Actor*> markeds{};
            for (auto & actor : Actor::actors)
                if (actor.second->isMarkedForDeath()) markeds.push(actor.second);

            using ID = Actor::ID;
            while (!markeds.empty()) {
                Actor *e = markeds.front();
                ID aid = e->id;
                Actor::actors.erase(aid);
                ID m = Actor::actors.rbegin()->first;
                if (m < aid) {
                    // at the end of the map, not fragmented
                    // retroactively clean up fragments (this is why fragments is a deque, not a queue)
                    while (m < Actor::fragments.back()) Actor::fragments.pop_back();
                } else {
                    Actor::fragments.push_back(aid);
                }
                delete e;
                markeds.pop();
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0.f, 0.f, 0.f, 0.f);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // render
    SDL_Rect rect = {100, 100, 480, 480 };
    FVec2 data = InputSystem()->getAnalogActionValue(InputSystem::AnalogAction::AnalogControls);
    printf("data: { %f, %f }\n", data.x, data.y);
    SDL_SetRenderDrawColor(renderer, uint8_t(data.x * float(0xFF)), uint8_t(data.y * float(0xFF)), 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
#ifdef NDEBUG
    GLenum err = glGetError();
    if (err != 0) SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%x %s", err, glewGetErrorString(err));
#endif
}