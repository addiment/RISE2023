#pragma once
#ifndef RISE_SPRITESHEET_H
#define RISE_SPRITESHEET_H

#include <SDL2/SDL.h>
#include <cstddef>
#include <cstdint>
#include "misc.h"

class SpriteSheet {
public:
    enum SheetEnum : size_t {
        WORLD,
        CHARACTERS,

        NUM_SHEETS
    };
    static EnumArray<SheetEnum, SpriteSheet> sheets;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface;
    bool isLoaded = false;
    unsigned int cellSize = 18;
    [[nodiscard]] inline const SDL_Rect getCell(unsigned int x = 0, unsigned int y = 0) const {
        return { (int)(x * cellSize), (int)(y * cellSize), (int)cellSize, (int)cellSize };
    }
    SpriteSheet() = default;
};

#endif // RISE_SPRITESHEET_H
