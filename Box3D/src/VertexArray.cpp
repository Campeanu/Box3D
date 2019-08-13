#include <Box3D/Renderer/VertexArray.hpp>

namespace box3d {

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &this->m_rendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &this->m_rendererID);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
    {
        bind();
        vbo.bind();
        const auto& elements = layout.getElements();    
        unsigned int offset = 0;
        for(unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);

            // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
            offset += element.count * VertexBufferElement::getSizeOfType(element.type);
        }

    }

    void VertexArray::bind() const
    {
        glBindVertexArray(this->m_rendererID);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

}