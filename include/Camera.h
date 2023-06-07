#pragma once

#ifndef TOOLKITENGINEV3_CAMERA_H
#define TOOLKITENGINEV3_CAMERA_H

#include "aces.h"
#include "misc.h"
#include "Manager.h"

class Camera : public Component {
public:
    // flip is value of SDL_RendererFlip
    void draw(SDL_Texture* texture, SDL_FRect srcrect, Transform transform, SDL_RendererFlip flip = SDL_FLIP_NONE);
    using Component::Component;
    float sceneSize = 1.0;
    FVec2 pos = { 0, 0 };
    float rot = 0;
};

class CameraActor : public Actor {
public:
    CameraActor() {
        getChildren().push_back(new Camera((Actor*)this));
    }
};

#endif //TOOLKITENGINEV3_CAMERA_H
