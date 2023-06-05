#include "tkev3.h"

class Player : public Actor {
public:
    void onPlay() override {
        Entity::onPlay();
    }

    void update(double delta) override {
        Entity::update(delta);
    }

    void render() override {
        Entity::render();
    }
};