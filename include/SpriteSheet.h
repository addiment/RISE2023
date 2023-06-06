#pragma once
#ifndef RISE_SPRITESHEET_H
#define RISE_SPRITESHEET_H

#include <SDL2/SDL.h>
#include <cstddef>
#include <cstdint>

class SpriteSheet {
public:
    enum class Sheet : size_t {
        WORLD,
        CHARACTERS,

        NUM_SHEETS
    };
    static SpriteSheet sheets[(size_t)Sheet::NUM_SHEETS];
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface;
    bool isLoaded = false;
    unsigned int cellSize = 16;
    inline const SDL_Rect getCell(unsigned int x = 0, unsigned int y = 0) {
        return { (int)(x * cellSize), (int)(y * cellSize), (int)cellSize, (int)cellSize };
    }
    SpriteSheet() = default;
};

#endif // RISE_SPRITESHEET_H
