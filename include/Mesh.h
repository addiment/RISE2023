#pragma once
#ifndef TOOLKITENGINEV3_MESH_H
#define TOOLKITENGINEV3_MESH_H

#include "aecs.h"
#include "Material.h"

class Mesh {
public:
    void draw(FVec2 position = {0, 0}) const;

    explicit Mesh(std::initializer_list<GLfloat> v, std::initializer_list<GLuint> i);
    explicit Mesh();
    ~Mesh();
protected:

    GLuint vao = 0, vbo = 0, ebo = 0;

    GLfloat* vertices = nullptr;
    size_t vertexCount = 0;
    size_t verticesSize = 0;

    GLuint* indexes = nullptr;
    size_t indexCount = 0;
    size_t indexesSize = 0;
};

class MeshComponent : public Component {
public:
    using Component::Component;
    explicit MeshComponent(Actor* p, Mesh* m);
    void setMesh(Mesh* m);
    [[nodiscard]] Mesh *getMesh();
protected:
    Mesh* mesh = nullptr;
};

#endif //TOOLKITENGINEV3_MESH_H
