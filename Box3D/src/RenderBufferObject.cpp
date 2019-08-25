#include <Box3D/Renderer/RenderBufferObject.hpp>

namespace box3d {

    RenderBufferObject::RenderBufferObject()
    {
        glGenBuffers(1, &this->m_rendererID);
        glBindRenderbuffer(GL_RENDERBUFFER, this->m_rendererID);
    }

    RenderBufferObject::~RenderBufferObject()
    {
    }

    void RenderBufferObject::createStorage(box3d::Application& app)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
    }

    void RenderBufferObject::bind() const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, this->m_rendererID);
    }

    void RenderBufferObject::unbind() const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

}
