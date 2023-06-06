#include "Scene.h"

Scene* Scene::currentScene = nullptr;

[[nodiscard]] Scene *Scene::getScene() { return currentScene; }

Scene *Scene::changeScene(Scene* scene) {
    if (currentScene) {
        // TODO: cleanup current scene
        delete currentScene;
    }
    currentScene = scene;
}

Actor::ID Scene::reserveId()  {
    if (fragments.empty()) {
        return (Actor::ID)actors.size();
    } else {
        Actor::ID top = fragments.front();
        fragments.pop_front();
        return top;
    }
}
