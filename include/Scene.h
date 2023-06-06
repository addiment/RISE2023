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
    [[nodiscard]] static Scene *getScene();

    virtual void update(double delta) = 0;
    virtual void onPlay() = 0;

    // returns the scene changed to
    static Scene *changeScene(Scene* scene);
    virtual ~Scene() = default;
private:
    static Scene *currentScene;

    friend class Actor;
    friend class Manager;
    std::map<Actor::ID, Actor*> actors{};
    std::deque<Actor::ID> fragments{};
    Actor::ID reserveId();
};

#endif // TOOLKITENGINEV3_SCENE_H
