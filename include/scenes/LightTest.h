#pragma once
#ifndef TOOLKITENGINEV3_LIGHTTEST_H
#define TOOLKITENGINEV3_LIGHTTEST_H

#include "tkev3.h"

namespace Scenes {

    class LightTest : public Scene {
    public:

        Texture* tex_shadowCaster = nullptr;
        Texture* tex_caster2 = nullptr;
        Texture* tex_grid = nullptr;

        Scene *create() override { return new LightTest(); }
        void onPlay() override { };
        void update(double delta) override {
            tex_grid->use(GL_TEXTURE0);
            mat_basic->use();
            mat_basic->setUniform("meshOffset", { 0.f, 0.f });
            mat_basic->setUniform("meshScale",  { 1.f, 1.f });
            mat_basic->setUniform("inTexture", 0);
            screenMesh->draw();
            uint64_t ticks = SDL_GetTicks64();
            float rot = (float(ticks) * 3.14f) / 1750.f;
            //    drawLight(
            //    FVec2(
            //    0.5f + (0.3f * cos(rot)),
            //    0.5f + (0.3f * sin(rot))
            //    ),
            //    FVec4(0.1f, 0.2f, 0.8f, 1.0f)
            //    );
            //    drawLight(
            //    FVec2(
            //    0.5f + (0.1f * cos(-rot)),
            //    0.5f + (0.1f * sin(-rot))
            //    ),
            //    FVec4(0.0f, 0.8f, 0.8f, 1.0f)
            //    );
            drawLight(lightDebug, FVec4(1.0f, 0.828125f, 0.5f, 1.0f));
            tex_shadowCaster->use(GL_TEXTURE2);
            mat_basic->use();
            mat_basic->setUniform("meshOffset", occluders[0].second.pos);
            mat_basic->setUniform("meshScale", occluders[0].second.scale);
            mat_basic->setUniform("inTexture", 2);
            screenMesh->draw();
            mat_basic->setUniform("meshOffset", occluders[1].second.pos);
            mat_basic->setUniform("meshScale", occluders[1].second.scale);
            tex_caster2->use(GL_TEXTURE2);
            screenMesh->draw();
        }
    };

}

#endif // TOOLKITENGINEV3_LIGHTTEST_H
