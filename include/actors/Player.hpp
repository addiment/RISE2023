#pragma once
#ifndef RISE_PLAYER_HPP
#define RISE_PLAYER_HPP

#include <tkev3.h>
#include "SpriteSheet.h"
#include "components/Sprite.hpp"

class Player : public Pawn {
public:

    struct {
        SoundSystem::Sound jump = SoundSystem::Sound{ SoundSystem::EFFECT, 96 };
    } sounds;

    // this could be a bit-field but idc
    struct {
        bool jump = false;
        bool special = false;
    } lastInputState;

    void onPlay() override {
        Pawn::onPlay();
        Pawn::setNickname("Player");
        setRelativeTransform(Transform { { 32, 32 }, { 48, 48 }, 0 });
        SDL_Log("Player PLAYED");
        SpriteSheet& sheet = SpriteSheet::sheets[SpriteSheet::CHARACTERS];
        const SDL_Rect rect = sheet.getCell(0, 0);
        new Sprite(
            this,
            Transform{ { 0, 0 }, { 2, 2 }, 0 },
            sheet.texture,
            &rect
        );
//        auto children = Actor::getChildren();
//        printf("children:\n");
//        for (auto & it : children) {
//            printf("%s\n", it->getPrintNickname());
//        }
        SoundSystem::armSound(&sounds.jump, "assets/jump.wav");
    }

    void onJump() { SoundSystem::playSound(&sounds.jump); }

    void onSpecial() { }

    void update(double delta) override {
        Pawn::update(delta);
        if (InputSystem::getCurrentActionSet() == InputSystem::ActionSet::GameControls) {
            // analog input
            FVec2 analogControlsValue = InputSystem::getAnalogActionValue(InputSystem::AnalogAction::AnalogControls);
            // TODO: this is really bad, need velocity and acceleration
            getRelativeTransform().pos.x += analogControlsValue.x * (float)delta * 8.f;
            getRelativeTransform().pos.y += analogControlsValue.y * (float)delta * 8.f;

            // Update digital input states
            {
                bool cjump = InputSystem::getDigitalActionValue(InputSystem::DigitalAction::Jump);
                if (lastInputState.jump != cjump && cjump) onJump();
                lastInputState.jump = cjump;
            }
            {
                bool cspecial = InputSystem::getDigitalActionValue(InputSystem::DigitalAction::Special);
                if (lastInputState.special != cspecial && cspecial) onSpecial();
                lastInputState.special = cspecial;
            }

        }

//        Transform gr = getRelativeTransform();
//        SDL_Log("Player UPDATED");
    }

    void render() override {
        Pawn::render();
//        SDL_Log("Player RENDERED");
    }
};

#endif // RISE_PLAYER_HPP