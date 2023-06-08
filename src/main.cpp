#include <tkev3.h>
#include "scenes/TestScene.hpp"
using namespace std;

// DEFINITION
void EnginePostInit() {

    {
        SpriteSheet *sheet = &(SpriteSheet::sheets[SpriteSheet::WORLD]);
        if (!sheet->isLoaded) {
            sheet->surface = IMG_Load("assets/tiles_packed.png");
            if (!sheet->surface) {
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", IMG_GetError());
                throw std::runtime_error("Failed to load world tileset!");
            }
            sheet->texture = SDL_CreateTextureFromSurface(Manager::renderer, sheet->surface);
            if (!sheet->texture) {
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", IMG_GetError());
                throw std::runtime_error("Failed to create texture for world tileset!");
            }
            sheet->cellSize = 18;
            sheet->isLoaded = true;
        }
    }

    {
        SpriteSheet *sheet = &(SpriteSheet::sheets[SpriteSheet::CHARACTERS]);
        if (!sheet->isLoaded) {
            sheet->surface = IMG_Load("assets/characters_packed.png");
            if (!sheet->surface) {
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", IMG_GetError());
                throw std::runtime_error("Failed to load character tileset!");
            }
            sheet->texture = SDL_CreateTextureFromSurface(Manager::renderer, sheet->surface);
            if (!sheet->texture) {
                SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", IMG_GetError());
                throw std::runtime_error("Failed to create texture for character tileset!");
            }
            sheet->cellSize = 24;
            sheet->isLoaded = true;
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Log("running");
#ifdef NDEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif
    return Manager::play(argc, argv, new Scenes::TestScene(), "Platformer");
}