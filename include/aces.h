#pragma once

#ifndef TOOLKITENGINEV3_ACES_H
#define TOOLKITENGINEV3_ACES_H

/**
 * Addie's [Actor -> Component -> Entity] System: ACES
 */

#include <cstddef>
#include <cstdint>
#include <vector>
#include <deque>
#include <map>
#include "misc.h"
//#include <unordered_map>
#include "Nickable.h"
#include "EzInputSys.h"

class Actor;
class Component;

// TODO: find a way to validate references

class Entity : public Nickable {
public:
    [[nodiscard]] std::vector<Entity *> & getChildren();
    [[nodiscard]] Entity* getParent() const;

    [[nodiscard]] virtual const bool canHaveChildren() const { return true; }

    virtual void onPlay();
    virtual void update(double delta);
    virtual void render();

    virtual ~Entity() = default;

    explicit Entity(Entity* prnt, Transform trans = {});
    explicit Entity(Component* prnt, Transform trans = {}) : Entity((Entity*)prnt, trans) { };
    explicit Entity(Actor* prnt, Transform trans = {}) : Entity((Entity*)prnt, trans) { };

    [[nodiscard]] inline Transform getAbsoluteTransform() const { // NOLINT(misc-no-recursion)
        auto* pp = getParent();
        if (pp) {
            return transform + pp->getAbsoluteTransform();
        } else return transform;
    }
    [[nodiscard]] inline Transform& getRelativeTransform() { return transform; }
    void setRelativeTransform(Transform t) { transform = t; }
private:
    friend class Manager;
    friend class Component;
    friend class Actor;

    std::vector<Entity*> children{};
    Entity* parent = nullptr;
    bool hasRunPlay = false;
    Transform transform = Transform{ { 0, 0 }, { 1, 1 }, 0 };

    explicit Entity() = default;
};

class Component : public Entity {
public:
    using Entity::Entity;
    explicit Component(Entity* prnt, Transform trans = {}) = delete;
};

class Actor : public Entity {
public:

    // look into copying later
    // Actor& operator=(const Actor&) = delete;  // Disallow copying
    explicit Actor();
    explicit Actor(Transform trans);
    [[nodiscard]] bool isMarkedForDeath() const { return markedForDeath; }
protected:
    friend class Manager;
    friend class Scene;

    typedef uint64_t ID;
    const ID id;

    ~Actor() override;

    bool markedForDeath = false;
};

class Pawn : public Actor {
public:
    using Actor::Actor;
// returns whether the input was consumed.
//    virtual bool sendInput(InputSystem::ActionSet set, InputSystem::AnalogAction analogAction, FVec2 analogActionData) { return false; }
//    virtual bool sendInput(InputSystem::ActionSet set, InputSystem::DigitalAction digitalAction, bool digitalActionData) { return false; }
};

#endif //TOOLKITENGINEV3_ACES_H
