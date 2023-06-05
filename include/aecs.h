#pragma once

#ifndef TOOLKITENGINEV3_AECS_H
#define TOOLKITENGINEV3_AECS_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include <deque>
#include <map>
//#include <unordered_map>
#include "Nickable.h"

class Actor;
class Component;

/**
 * TODO: find a way to validate references
 */

class Entity : public Nickable {
public:
    virtual std::vector<Entity *> & getChildren();
    virtual Entity* getParent();
    
    virtual void onPlay() { };
    virtual void update(double delta);
    virtual void render();

    virtual ~Entity() = default;

    explicit Entity() = default;
    explicit Entity(Entity* prnt) : parent(prnt) { };
    explicit Entity(Component* prnt) : parent((Entity*)prnt) { };
    explicit Entity(Actor* prnt) : parent((Entity*)prnt) { };
private:
    std::vector<Entity*> children{};
    Entity* parent = nullptr;
};

class Component : public Entity {
public:
    using Entity::Entity;
    explicit Component() = delete;
};

class Actor : public Entity {
public:

    Actor& operator=(const Actor&) = delete;  // Disallow copying
    explicit Actor();
    [[nodiscard]] bool isMarkedForDeath();
protected:
    friend class Manager;

    ~Actor() override;

    bool markedForDeath = false;
private:
    friend class Manager;
    typedef uint64_t ID;

    const ID id;

    static std::map<ID, Actor*> actors;
    static std::deque<ID> fragments;
    static ID reserveId();
};

#endif //TOOLKITENGINEV3_AECS_H
