#include "Scene.h"

Scene* Scene::currentScene = nullptr;

[[nodiscard]] Scene *Scene::getScene() { return currentScene; }