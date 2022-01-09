#include "mesh.h"

#include "glad/glad.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicies.size(), indicies.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    size = indicies.size();
}

Mesh::Mesh(Mesh&& rhs) noexcept
    : vao(rhs.vao)
    , vbo(rhs.vbo)
    , ebo(rhs.ebo)
    , size(rhs.size)
{
    rhs.vao = 0;
    rhs.vbo = 0;
    rhs.ebo = 0;
    rhs.size = 0;
}

Mesh& Mesh::operator=(Mesh&& rhs) noexcept
{
    destroy();

    vao = rhs.vao;
    vbo = rhs.vbo;
    ebo = rhs.ebo;
    size = rhs.size;

    rhs.vao = 0;
    rhs.vbo = 0;
    rhs.ebo = 0;
    rhs.size = 0;

    return *this;
}

Mesh::~Mesh()
{
    destroy();
}

void Mesh::draw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    vao = 0;
    vbo = 0;
    ebo = 0;
    size = 0;
}
