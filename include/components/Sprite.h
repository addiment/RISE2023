#pragma once
#ifndef RISE_SPRITE_H
#define RISE_SPRITE_H

#include <aces.h>

class Sprite : public Component {
public:
    void render() override {
//        if (texture) Manager::scene->
//SDL_RenderCopyExF(Manager::renderer, texture, )
    }
    using Component::Component;
    Sprite(Actor* parent, SDL_Texture* tex) : Component(parent), texture(tex) {

    }
protected:
    SDL_Texture* texture = nullptr;
};

#endif // RISE_SPRITE_H
