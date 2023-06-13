#pragma once
#ifndef RISE_PLAYERHUD_H
#define RISE_PLAYERHUD_H

#include <tkev3.h>
#include <SpriteSheet.h>
#include <components/UserInterface.h>

class PlayerHUD : public UserInterface {
public:

    using UserInterface::UserInterface;

    SpriteSheet& worldSheet = SpriteSheet::sheets[SpriteSheet::WORLD];
    SDL_Rect heartSrcRect[3] = {};

    SDL_FPoint topLeft = { 9, 9 };
    // maxHealth = numHearts * 2
    const int numHearts = 2;
    int health = 2;
    float heartScale = 2;

    void onPlay() override {
        UserInterface::onPlay();
        heartSrcRect[0] = worldSheet.getCell(4, 2);
        heartSrcRect[1] = worldSheet.getCell(5, 2);
        heartSrcRect[2] = worldSheet.getCell(6, 2);
    }

    void update(double delta) override {
        UserInterface::update(delta);
    }

    void render() override {
        UserInterface::render();
        for (int i = 0; i < numHearts; i++) {
            const SDL_FRect dst = {
                topLeft.x + heartScale * (float)(worldSheet.cellSize * i),
                topLeft.y,
                heartScale * (float)worldSheet.cellSize,
                heartScale * (float)worldSheet.cellSize
            };
            int heartIndex = 1;
            int j = health - (i * 2);
            if (j >= 2) heartIndex = 0;
            else if (j <= 0) heartIndex = 2;
            SDL_RenderCopyF(Manager::renderer, worldSheet.texture, &heartSrcRect[heartIndex], &dst);
        }
    }
};

#endif // RISE_PLAYERHUD_H
