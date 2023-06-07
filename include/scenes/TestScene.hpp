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

            activePawn = new Player();
            activeCamera = (new CameraActor())->camera;
        };
        void update(double delta) override {
        }

    };

}

#endif // RISE_TESTSCENE_HPP
