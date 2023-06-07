#pragma once
#ifndef TOOLKITENGINEV3_SCENE_H
#define TOOLKITENGINEV3_SCENE_H

#include "misc.h"
#include "aces.h"
#include "Camera.h"
#include <vector>
#include <deque>
#include <map>

class Scene {
public:

    virtual void update(double delta) = 0;
    virtual void onPlay() = 0;

    virtual ~Scene() = default;

    [[nodiscard]] Camera* getActiveCamera() const;
    [[nodiscard]] Pawn* getActivePawn() const;
    virtual RETURN_MAY_BE_NULL const char* getSceneName() { return nullptr; }

protected:
    friend class Actor;
    friend class Manager;

    Camera* activeCamera = nullptr;
    Pawn* activePawn = nullptr;

    std::map<Actor::ID, Actor*> actors{};
    std::deque<Actor::ID> fragments{};
private:
    // might be redundant but idc
    friend class Actor;
    friend class Manager;

    Actor::ID reserveId();
};

#endif // TOOLKITENGINEV3_SCENE_H
