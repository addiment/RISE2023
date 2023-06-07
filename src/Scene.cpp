#include "Scene.h"

Camera *Scene::getActiveCamera() const { return activeCamera; }
Pawn *Scene::getActivePawn() const { return activePawn; }

Actor::ID Scene::reserveId()  {
    if (fragments.empty()) {
        return (Actor::ID)actors.size();
    } else {
        Actor::ID top = fragments.front();
        fragments.pop_front();
        return top;
    }
}
