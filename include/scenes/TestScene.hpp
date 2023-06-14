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

        SoundSystem::Sound bgm = SoundSystem::Sound(SoundSystem::MUSIC, 64, "TestScene BGM");

        const char* getSceneName() override { return "TestScene"; }

        void onPlay() override {
            SDL_Log("TestScene Played!");

            {
                bool res = SoundSystem::armSound(&bgm, "assets/jaunty-gumption_146_full-mix.mp3");
                if (!res) throw std::runtime_error(Mix_GetError());
                res = SoundSystem::setMusic(&bgm);
                if (!res) throw std::runtime_error(Mix_GetError());
                SoundSystem::playMusic();
            }

            activePawn = new Player();
            activeCamera = (new CameraActor())->camera;
        };

        void update(double delta) override { }

    };

}

#endif // RISE_TESTSCENE_HPP
