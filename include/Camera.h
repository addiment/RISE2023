#pragma once

#ifndef TOOLKITENGINEV3_CAMERA_H
#define TOOLKITENGINEV3_CAMERA_H

#include "aces.h"
#include "misc.h"

class Camera : public Component {
public:
    // flip is value of SDL_RendererFlip
    void draw(SDL_Texture* texture, const SDL_Rect* srcrect, Transform t, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    using Component::Component;

    [[nodiscard]] inline float getPixelsPerUnit() const { return pixelsPerUnit; }
    void setPixelsPerUnit(float pPU) { Camera::pixelsPerUnit = pPU; }

    Camera(Component* prnt, float pPU) :  Component(prnt), pixelsPerUnit(pPU) { }
    Camera(Actor* prnt, float pPU) :  Component(prnt), pixelsPerUnit(pPU) { }
protected:
    float pixelsPerUnit = 1.0;
};

class CameraActor : public Actor {
public:
    Camera* camera = new Camera((Actor*)this);
    using Actor::Actor;
    explicit CameraActor(float pPU) : CameraActor() {
        camera->setPixelsPerUnit(pPU);
    }
};

#endif //TOOLKITENGINEV3_CAMERA_H
