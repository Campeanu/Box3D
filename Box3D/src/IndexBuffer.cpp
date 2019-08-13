#include <Box3D/Renderer/IndexBuffer.hpp>

namespace box3d {

    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
        : m_count { count }
    {
        glGenBuffers(1, &this->m_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &this->m_rendererID);
    }
    
    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_rendererID);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}