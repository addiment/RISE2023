#pragma once
#ifndef RISE_SPRITE_HPP
#define RISE_SPRITE_HPP

#include <tkev3.h>

class Sprite : public Component, protected Primitive {
public:
    using Component::Component;

    void update(double delta) override {
        Component::update(delta);
        Entity* p = Component::getParent();
        if (p) printf("%s\n", p->getPrintNickname());
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
//        printf("x = %f, y = %f\n", ga.pos.x, ga.pos.y);
        if (cam) cam->draw(texture, srcRect, ga);
    }
    [[nodiscard]] inline SDL_Texture *getTexture() const { return texture; }
    [[nodiscard]] inline const SDL_Rect *getSrcRect() const { return srcRect; }

    void setTexture(SDL_Texture *pTexture) { Sprite::texture = pTexture; }
    inline void setSrcRect(const SDL_Rect* rect) {
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
};

#endif // RISE_SPRITE_HPP
