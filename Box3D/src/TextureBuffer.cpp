#include <Box3D/Renderer/TextureBuffer.hpp>

namespace box3d {

    TextureBuffer::TextureBuffer()
    {
        glGenTextures(1, &this->m_rendererID);
        glBindTexture(GL_TEXTURE_2D, this->m_rendererID);
    }

    TextureBuffer::~TextureBuffer()
    {

    }

    void TextureBuffer::createTexImage2D(box3d::Application& app)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, app.GetWindow().GetWidth(), app.GetWindow().GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    }

    void TextureBuffer::setTextureAtributes()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void TextureBuffer::bind()   const
    {
        glBindTexture(GL_TEXTURE_2D, this->m_rendererID);
    }

    void TextureBuffer::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }


}
