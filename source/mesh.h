#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <vector>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    //glm::vec2 uv;
};

struct Mesh
{
    unsigned int vao, vbo, ebo, size;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies);
    Mesh(Mesh&&) noexcept;
    Mesh& operator=(Mesh&&) noexcept;
    ~Mesh();

    void draw();
    void destroy();
};