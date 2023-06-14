#pragma once
#ifndef TOOLKITENGINEV3_SPRITE_HPP
#define TOOLKITENGINEV3_SPRITE_HPP

#include <tkev3.h>

class Sprite : public Component {
public:
    using Component::Component;

    void update(double delta) override {
        Component::update(delta);
//        Entity* p = getParent();
//        if (p) printf("%s\n", p->getPrintNickname());
//        auto children = Component::getChildren();
//        printf("children:\n");
//        for (auto & it : children) {
//            printf("%s\n", it->getPrintNickname());
//        }
    }

    void render() override {
        Component::render();
        Camera* cam = Manager::getActiveCamera();
        Transform ga = getAbsoluteTransform();
        if (cam) cam->draw(texture, srcRect, ga);
    }
    [[nodiscard]] inline SDL_Texture *getTexture() const { return texture; }
    [[nodiscard]] inline const SDL_Rect *getSrcRect() const { return srcRect; }
    [[nodiscard]] inline float getUnitsPerPixel() const { return unitsPerPixel; }

    void setUnitsPerPixel(float uPP) { Sprite::unitsPerPixel = uPP; }
    void setTexture(SDL_Texture *tex) { Sprite::texture = tex; }
    void setSrcRect(const SDL_Rect* rect) {
        if (rect) {
            *Sprite::srcRect = *rect;
            return;
        }
        delete srcRect;
        srcRect = nullptr;
    }

    explicit Sprite(Actor* parent, Transform t, SDL_Texture* texture = nullptr, ARGUMENT_MAY_BE_NULL const SDL_Rect* rect = nullptr) : Component(parent), texture(texture) {
        setRelativeTransform(t);
        if (rect) {
            srcRect = new SDL_Rect();
            (*srcRect) = *rect;
        }
    }

    ~Sprite() override { delete srcRect; }
protected:
    SDL_Texture* texture = nullptr;
    SDL_Rect* srcRect = nullptr;
    float unitsPerPixel = 1.0;
};

class SpriteActor : public Actor {
public:
    Sprite* sprite = new Sprite((Actor*)this);
    using Actor::Actor;
    explicit SpriteActor(float uPP) : SpriteActor() {
        sprite->setUnitsPerPixel(uPP);
    }
};

#endif // TOOLKITENGINEV3_SPRITE_HPP
