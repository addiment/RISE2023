#include "Scene.h"

Actor::ID Scene::reserveId()  {
    if (fragments.empty()) {
        return (Actor::ID)actors.size();
    } else {
        Actor::ID top = fragments.front();
        fragments.pop_front();
        return top;
    }
}
