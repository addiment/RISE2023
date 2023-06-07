#pragma once
#ifndef TOOLKITENGINEV3_SCENE_H
#define TOOLKITENGINEV3_SCENE_H

#include "misc.h"
#include "aces.h"
#include <vector>
#include <deque>
#include <map>

class Scene {
public:

    virtual void update(double delta) = 0;
    virtual void onPlay() = 0;

    virtual ~Scene() = default;

private:
    friend class Actor;
    friend class Manager;
    std::map<Actor::ID, Actor*> actors{};
    std::deque<Actor::ID> fragments{};
    Actor::ID reserveId();
};

#endif // TOOLKITENGINEV3_SCENE_H
