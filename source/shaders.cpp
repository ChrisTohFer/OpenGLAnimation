#include "shaders.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(const char* vert, const char* frag)
{
    int success;
    char log[512];
    
    auto vert_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_id, 1, &vertex_shader, 0);
    glCompileShader(vert_id);
    glGetShaderiv(vert_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vert_id, 512, nullptr, log);
        std::cout << "Error compiling vertex shader:\n" << log << "\n";
        glDeleteShader(vert_id);
        return;
    }

    auto frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_id, 1, &fragment_shader, 0);
    glCompileShader(frag_id);
    glGetShaderiv(frag_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(frag_id, 512, nullptr, log);
        std::cout << "Error compiling fragment shader:\n" << log << "\n";
        glDeleteShader(frag_id);
        return;
    }

    id = glCreateProgram();
    glAttachShader(id, vert_id);
    glAttachShader(id, frag_id);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, log);
        std::cout << "Error linking shaderprogram:\n" << log << "\n";
        glDeleteProgram(id);
        return;
    }

    glUseProgram(id);

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
}
ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept
    : id(rhs.id)
{
    rhs.id = 0;
}
ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept
{
    delete_program();

    id = rhs.id;
    rhs.id = 0;

    return *this;
}
ShaderProgram::~ShaderProgram()
{
    delete_program();
}

void ShaderProgram::set_mat4(const char* name, const glm::mat4& mat)
{
    auto location = glGetUniformLocation(id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::bind()
{
    glUseProgram(id);
}

void ShaderProgram::delete_program()
{
    if (id != 0)
        glDeleteProgram(id);

    id = 0;
}
