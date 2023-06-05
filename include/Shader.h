#pragma once
#ifndef TOOLKITENGINEV3_SHADER_H
#define TOOLKITENGINEV3_SHADER_H

#include "misc.h"
#include "Texture.h"
#include "Nickable.h"

class Shader: public Nickable {
public:
    enum ShaderType {
        // INVALID should never be used and will cause issues
        INVALID = 0,
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

    void use();
    [[nodiscard]] bool isCompiled() const;

    bool create(const GLchar* source);
    bool createFromFile(const char* sourceFile);
    void destroy();

    [[nodiscard]] ShaderType getShaderType() const;
    [[nodiscard]] GLuint getId() const;

    ~Shader();
    explicit Shader(ShaderType type);
    explicit Shader(ShaderType type, const char* nickname);
protected:

    ShaderType shaderType = INVALID;
    GLuint id = 0;
    bool compiled = false;

private:
    Shader() = default;
};

extern Shader* shader_v_basic;
extern Shader* shader_f_basic;

#endif // TOOLKITENGINEV3_SHADER_H
