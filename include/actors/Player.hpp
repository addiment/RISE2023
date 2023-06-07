#pragma once
#ifndef RISE_PLAYER_HPP
#define RISE_PLAYER_HPP

#include <tkev3.h>
#include "SpriteSheet.h"
#include "components/Sprite.hpp"

class Player : public Pawn, public Primitive {
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
        Transform gr = getRelativeTransform();
//        SDL_Log("Player UPDATED");
    }

    void render() override {
        Pawn::render();
//        SDL_Log("Player RENDERED");
    }

    bool sendInput(InputSystem::ActionSet set, InputSystem::AnalogAction analogAction, FVec2 analogActionData) override {
        switch (set) {

            case InputSystem::ActionSet::GameControls: {
                switch (analogAction) {

                    case InputSystem::AnalogAction::AnalogControls: {
                        getRelativeTransform().pos.x += analogActionData.x;
                        getRelativeTransform().pos.y += analogActionData.y;
                        break;
                    }

                    default: break;
                }
                return true;
            }

            case InputSystem::ActionSet::MenuControls:
            default: break;
        }
        return false;
    }

    bool sendInput(InputSystem::ActionSet set, InputSystem::DigitalAction digitalAction, bool digitalActionData) override {
        return Pawn::sendInput(set, digitalAction, digitalActionData);
    }
};

#endif // RISE_PLAYER_HPP