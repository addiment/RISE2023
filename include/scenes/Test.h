#pragma once
#ifndef TOOLKITENGINEV3_LIGHTTEST_H
#define TOOLKITENGINEV3_LIGHTTEST_H

#include "tkev3.h"

#include "SpriteSheet.h"

namespace Scenes {


    class Test : public Scene {
    public:

        void onPlay() override {
            {
                SpriteSheet *sheet = &(SpriteSheet::sheets[(size_t)SpriteSheet::Sheet::WORLD]);
                if (!sheet->isLoaded) {
                    sheet->surface = IMG_Load("assets/tiles_packed.png");
                    sheet->texture = SDL_CreateTextureFromSurface(Manager::renderer, sheet->surface);
                    sheet->isLoaded = true;
                }
            }

            {
                SpriteSheet *sheet = &(SpriteSheet::sheets[(size_t) SpriteSheet::Sheet::CHARACTERS]);
                if (!sheet->isLoaded) {
                    sheet->surface = IMG_Load("assets/characters_packed.png");
                    sheet->texture = SDL_CreateTextureFromSurface(Manager::renderer, sheet->surface);
                    sheet->isLoaded = true;
                }
            }
        };
        void update(double delta) override {
        }

    };

    Scene* Scene_Test() { return new Test(); }

}

#endif // TOOLKITENGINEV3_LIGHTTEST_H
