#include <tkev3.h>

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Log("running");
#ifdef NDEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif
    return Manager()->play(argc, argv);
}