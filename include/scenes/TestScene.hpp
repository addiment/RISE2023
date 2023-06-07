#pragma once
#ifndef RISE_TESTSCENE_HPP
#define RISE_TESTSCENE_HPP

#include <tkev3.h>
#include <exception>
#include <stdexcept>
#include "SpriteSheet.h"
#include "actors/Player.hpp"

namespace Scenes {

    class TestScene : public Scene {
    public:

        const char* getSceneName() override { return "TestScene"; }

        void onPlay() override {
            SDL_Log("TestScene Played!");

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

            activePawn = new Player();
            activeCamera = (new CameraActor())->camera;
        };
        void update(double delta) override {
        }

    };

}

#endif // RISE_TESTSCENE_HPP
