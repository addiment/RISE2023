#include "tkev3.h"
#include "components/Sprite.h"

class Player : public Actor {
public:

    void onPlay() override {
        Entity::onPlay();
//        getChildren().push_back(new Sprite(this, ));
    }

    void update(double delta) override {
        Entity::update(delta);
    }

    void render() override {
        Entity::render();
    }
};