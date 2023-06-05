#pragma once
#ifndef TOOLKITENGINEV3_MATERIAL_H
#define TOOLKITENGINEV3_MATERIAL_H

#include "misc.h"
#include "Texture.h"
#include "Nickable.h"
#include "Shader.h"

// Wrapper for OpenGL shader programs
class Material: public Nickable {
public:

    /* TODO:
     * - Shader caching (see https://www.khronos.org/opengl/wiki/Shader_Compilation#Binary_upload)
     * - Better initialization system
     */

    typedef struct MaterialBinary{
        GLenum format;
        void *data;
        GLsizei length;
    } MaterialBinary;

    void use();
    [[nodiscard]] bool isReady() const;

    bool create(Shader *vert, Shader *frag, const char *zeroBind);
    // Attach shaders
    // bool add();
    // Link program
    // bool link();
    void destroy();

    [[nodiscard]] Shader* getVertexShader() const;
    [[nodiscard]] Shader* getFragmentShader() const;
    [[nodiscard]] GLuint getShaderProgram() const;

    // TODO: there are more uniform types than just int, silly
    void setUniform(const char *name, bool value) const;
    void setUniform(const char *name, int value) const;
    void setUniform(const char *name, float value) const;
    void setUniform(const char *name, FVec2 value) const;
    void setUniform(const char *name, FVec3 value) const;
    void setUniform(const char *name, FVec4 value) const;

    Material() = default;
    using Nickable::Nickable;
    ~Material();
protected:

    bool isLinked = false;

    Shader *vertex = nullptr, *fragment = nullptr;
    GLuint program = 0;
};

extern Material* mat_basic;

#endif //TOOLKITENGINEV3_MATERIAL_H
