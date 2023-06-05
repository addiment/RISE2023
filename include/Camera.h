#pragma once

#ifndef TOOLKITENGINEV3_CAMERA_H
#define TOOLKITENGINEV3_CAMERA_H

#include "aecs.h"

class Camera : public Component {
public:
    using Component::Component;
};

class CameraActor : public Actor {
public:
    CameraActor() {
        getChildren().push_back(new Camera((Actor*)this));
    }
};

#endif //TOOLKITENGINEV3_CAMERA_H
