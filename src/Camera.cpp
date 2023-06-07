#include "Camera.h"
#include "Manager.h"
#include <cmath>

void Camera::draw(SDL_Texture *texture, const SDL_Rect* srcrect, Transform t, SDL_RendererFlip flip) const {
    if (!texture) return;

    Transform privTrans = getAbsoluteTransform();

    double theta = (t.rot + (2.0 * PI) - (double)privTrans.rot);
    // scale isn't scale- it's bounding box size. pos is the center of the bb,
    // so convert that to top-left coordinates.
    FVec2 tl = {
    t.pos.x - (t.scale.x / 2),
    t.pos.y - (t.scale.y / 2)
    };
    FVec2 d = { (tl.x - privTrans.pos.x), (tl.y - privTrans.pos.y) };
    FVec2 tlRotated = {
        float(t.scale.x * (cos(theta) * d.x - sin(theta) * d.y) / privTrans.scale.x),
        float(t.scale.y * (cos(theta) * d.y + sin(theta) * d.y) / privTrans.scale.x)
    };

    const SDL_FRect rect = {tlRotated.x, tlRotated.y, t.scale.x / privTrans.scale.x, t.scale.y / privTrans.scale.x };
    // apparently my home-grown rotation math was unnecessary? oops, lmao
    // too lazy to simplify ngl
    const SDL_FPoint center = { 0, 0 };
    // TODO: fix this
    const SDL_Rect srect = { srcrect->x, srcrect->y, srcrect->w, srcrect->h };
    SDL_RenderCopyExF(Manager::renderer, texture, &srect, &rect, t.rot - privTrans.rot, &center, (SDL_RendererFlip)flip);
}