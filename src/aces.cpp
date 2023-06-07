#include "aces.h"
#include "Manager.h"

using namespace std;

// clang-tidy thinks this is recursive. Sorta? Not really.
// Every entity should render its children because only the root entities (actors) will be explicitly requested to render by the engine
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

void Entity::onPlay() { }

Actor::Actor() : id((Manager::getScene() ? Manager::getScene()->reserveId() : 0)) {
    Manager::getScene()->actors[id] = this;
}

Actor::~Actor() {
    this->markedForDeath = true;
}