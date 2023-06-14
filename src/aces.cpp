#include "aces.h"
#include "Manager.h"

using namespace std;

// clang-tidy thinks a lot of these are recursive. Sorta? Not really.
// Every entity should render its children because only the root entities (actors) will be explicitly requested to render by the engine.
// Also, an entity should/will never be parented to itself.

void Entity::render() { // NOLINT(misc-no-recursion)
    for (Entity* it : getChildren()) {
        it->render();
    }
}

void Entity::update(double delta) { // NOLINT(misc-no-recursion)
    for (Entity* it : getChildren()) {
        it->update(delta);
    }
}

vector<Entity *> & Entity::getChildren() { return children; }

Entity *Entity::getParent() const { return parent; }

void Entity::onPlay() { // NOLINT(misc-no-recursion)
    if (!hasRunPlay) for (auto & it : children) it->onPlay();
}

Entity::Entity(Entity* prnt, Transform trans) : parent(prnt), handle(new Handle(this)), transform(trans) {
    if (!parent->canHaveChildren()) throw runtime_error("Tried to attach a new entity to an entity that can't have children!");
    parent->getChildren().push_back(this);
};


Actor::Actor() : id((Manager::getScene() ? Manager::getScene()->reserveId() : 0)) {
    Manager::getScene()->actors[id] = this;
}

Actor::Actor(Transform trans) : Actor() {
    transform = trans;
}

Actor::~Actor() {
    this->markedForDeath = true;
}