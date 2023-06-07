#pragma once

#ifndef TOOLKITENGINEV3_CAMERA_H
#define TOOLKITENGINEV3_CAMERA_H

#include "aces.h"
#include "misc.h"

class Camera : public Component, public Primitive {
public:
    // flip is value of SDL_RendererFlip
    void draw(SDL_Texture* texture, const SDL_Rect* srcrect, Transform t, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    using Component::Component;
};

class CameraActor : public Actor {
public:
    Camera* camera = new Camera((Actor*)this);
    CameraActor() { }
};

#endif //TOOLKITENGINEV3_CAMERA_H
