#pragma once
#ifndef TOOLKITENGINEV3_TEXTURE_H
#define TOOLKITENGINEV3_TEXTURE_H

#include "misc.h"

class Texture {
public:
    explicit Texture(const char* fname, GLint filter = GL_LINEAR, GLint mipFilter = GL_LINEAR);
    // Binds and activates this as the current texture at the specified OpenGL index
    void use(int index = GL_TEXTURE0) const;
    ~Texture();
protected:
    friend class Framebuffer;
    Texture() = default;
//    SDL_Texture* sdlTexture = nullptr;
    IVec2 size = { -1, -1 };
    GLuint id = 0;
};

#endif //TOOLKITENGINEV3_TEXTURE_H
