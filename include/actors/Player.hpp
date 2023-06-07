#pragma once
#ifndef RISE_PLAYER_HPP
#define RISE_PLAYER_HPP

#include <tkev3.h>
#include "SpriteSheet.h"
#include "components/Sprite.hpp"

class Player : public Pawn {
public:

    void onPlay() override {
        Pawn::onPlay();
        Pawn::setNickname("Player");
        setRelativeTransform(Transform { { 32, 32 }, { 48, 48 }, 0 });
        SDL_Log("Player PLAYED");
        SpriteSheet& sheet = SpriteSheet::sheets[SpriteSheet::CHARACTERS];
        const SDL_Rect rect = sheet.getCell(0, 0);
        new Sprite(
            this,
            getRelativeTransform(),
            sheet.texture,
            &rect
        );
//        auto children = Actor::getChildren();
//        printf("children:\n");
//        for (auto & it : children) {
//            printf("%s\n", it->getPrintNickname());
//        }
    }

    void update(double delta) override {
        Pawn::update(delta);
        if (InputSystem::getCurrentActionSet() == InputSystem::ActionSet::GameControls) {
            FVec2 analogControlsValue = InputSystem::getAnalogActionValue(InputSystem::AnalogAction::AnalogControls);
            getRelativeTransform().pos.x += analogControlsValue.x * (float)delta * 8.f;
            getRelativeTransform().pos.y += analogControlsValue.y * (float)delta * 8.f;
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