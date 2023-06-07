#include "Camera.h"
#include <cmath>

void Camera::draw(SDL_Texture *texture, SDL_FRect srcrect, Transform transform, SDL_RendererFlip flip) {
    double theta = (transform.rot + (2.0 * PI) - (double)rot);
    // scale isn't scale- it's bounding box size. pos is the center of the bb,
    // so convert that to top-left coordinates.
    FVec2 tl = {
        transform.pos.x - (transform.scale.x / 2),
        transform.pos.y - (transform.scale.y / 2)
    };
    FVec2 d = { (tl.x - pos.x), (tl.y - pos.y) };
    FVec2 tlRotated = {
        float(transform.scale.x * (cos(theta) * d.x - sin(theta) * d.y) / sceneSize),
        float(transform.scale.y * (cos(theta) * d.y + sin(theta) * d.y) / sceneSize)
    };

    const SDL_FRect rect = { tlRotated.x, tlRotated.y, transform.scale.x / sceneSize, transform.scale.y / sceneSize };
    // apparently my home-grown rotation math was unnecessary? oops, lmao
    // too lazy to simplify ngl
    const SDL_FPoint center = { 0, 0 };
    SDL_RenderCopyExF(Manager::renderer, texture, (const SDL_Rect *)(&srcrect), &rect, transform.rot - rot, &center, (SDL_RendererFlip)flip);
}