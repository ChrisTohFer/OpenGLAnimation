#include "vertices.h"

#include "glad/glad.h"
#include <iostream>

VertexArrayObject::VertexArrayObject(const VertexBuffer& vertices, int stride_value, const IndexBuffer* indicies)
    : element_buffer_id(0)
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);

    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    stride = stride_value;

    if (indicies != nullptr)
    {
        glGenBuffers(1, &element_buffer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies->size() * sizeof(int), indicies->data(), GL_STATIC_DRAW);
    }
}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& rhs) noexcept
    : id(rhs.id)
    , vertex_buffer_id(rhs.vertex_buffer_id)
    , element_buffer_id(rhs.element_buffer_id)
    , stride(rhs.stride)
{
    rhs.id = 0;
    rhs.vertex_buffer_id = 0;
    rhs.element_buffer_id = 0;
    rhs.stride = 0;
}

VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& rhs) noexcept
{
    delete_object_and_buffers();

    id = rhs.id;
    vertex_buffer_id = rhs.vertex_buffer_id;
    element_buffer_id = rhs.element_buffer_id;
    stride = rhs.stride;

    rhs.id = 0;
    rhs.vertex_buffer_id = 0;
    rhs.element_buffer_id = 0;
    rhs.stride = 0;

    return *this;
}

VertexArrayObject::~VertexArrayObject()
{
    delete_object_and_buffers();
}

void VertexArrayObject::bind()
{
    glBindVertexArray(id);
}

void VertexArrayObject::delete_object_and_buffers()
{
    glDeleteVertexArrays(1, &id);
    glDeleteBuffers(1, &vertex_buffer_id);
    glDeleteBuffers(1, &element_buffer_id);

    id = 0;
    vertex_buffer_id = 0;
    element_buffer_id = 0;
}

bool VertexArrayObject::has_element_buffer() const
{
    return element_buffer_id != 0;
}

void VertexArrayObject::add_vertex_attribute_pointer(int index, int size, bool normalised, int offset)
{
    glVertexAttribPointer(index, size, GL_FLOAT, normalised ? GL_TRUE : GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
}
