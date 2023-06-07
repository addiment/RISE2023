#include <tkev3.h>
#include "scenes/TestScene.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    SDL_Log("running");
#ifdef NDEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif
    return Manager::play(argc, argv, new Scenes::TestScene());
}