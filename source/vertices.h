#pragma once

#include <vector>

using VertexBuffer = std::vector<float>;
using IndexBuffer = std::vector<int>;

struct VertexArrayObject
{
    unsigned int id;
    unsigned int vertex_buffer_id;
    unsigned int element_buffer_id;
    int          stride;

    VertexArrayObject(const VertexBuffer& vertices, int stride_value, const IndexBuffer* indicies = nullptr);
    VertexArrayObject(VertexArrayObject&&) noexcept;
    VertexArrayObject& operator=(VertexArrayObject&&) noexcept;
    ~VertexArrayObject();
    
    void bind();
    void delete_object_and_buffers();
    bool has_element_buffer() const;
    void add_vertex_attribute_pointer(int index, int size, bool normalised, int offset);
};