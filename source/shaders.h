#pragma once

#include "glm/mat4x4.hpp"

const inline char* vertex_shader = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 world;\n"
    "uniform mat4 view;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = view * world * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const inline char* fragment_shader =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

struct ShaderProgram
{
    unsigned int id;

    ShaderProgram(const char* vert, const char* frag);
    ShaderProgram(ShaderProgram&&) noexcept;
    ShaderProgram& operator=(ShaderProgram&&) noexcept;
    ~ShaderProgram();

    void set_mat4(const char* name, const glm::mat4&);
    void bind();
    void delete_program();
};