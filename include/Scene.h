#pragma once
#ifndef TOOLKITENGINEV3_SCENE_H
#define TOOLKITENGINEV3_SCENE_H

class Scene {
public:

    // MUST be implemented! Factory pattern.
    virtual Scene* create();

    [[nodiscard]] static Scene *getScene();

    virtual void update(double delta) = 0;
    virtual void onPlay() = 0;

    // returns the scene changed to
    static Scene *changeScene();
private:
    static Scene *currentScene;
};

namespace Scenes {
//    Scene*
    // add scenes here
}

#endif // TOOLKITENGINEV3_SCENE_H
