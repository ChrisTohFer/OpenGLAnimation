#include "shaders.h"

#include "glad/glad.h"

ShaderProgram::ShaderProgram(const char* vert, const char* frag)
{
    auto vert_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_id, 1, &vertex_shader, 0);
    glCompileShader(vert_id);

    auto frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_id, 1, &fragment_shader, 0);
    glCompileShader(frag_id);

    id = glCreateProgram();
    glAttachShader(id, vert_id);
    glAttachShader(id, frag_id);
    glLinkProgram(id);
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
