#include <Box3D/Renderer/VertexBuffer.hpp>

namespace box3d {

    VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    {
        glGenBuffers(1, &this->m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, this->m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &this->m_rendererID);
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, this->m_rendererID);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}