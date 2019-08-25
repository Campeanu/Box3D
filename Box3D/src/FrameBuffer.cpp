#include <Box3D/Renderer/FrameBuffer.hpp>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif


namespace box3d {

    FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &this->m_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, this->m_rendererID);
    }

    FrameBuffer::~FrameBuffer()
    {

    }

    void FrameBuffer::AddBuffer(box3d::RenderBufferObject& rbo, box3d::TextureBuffer& tcb, box3d::Application& app)
    {
        this->bind();

        tcb.bind();

        tcb.createTexImage2D(app);
        tcb.setTextureAtributes();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tcb.getRendererID(), 0);

        rbo.bind();
        rbo.createStorage(app);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo.getRendererID());

        this->isComplete();
    }

    void FrameBuffer::isComplete()
    {
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }

    void FrameBuffer::clear(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha, bool depth)
    {
        glClearColor(red, green, blue, alpha);

        if(depth == true)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        else
            glClear(GL_COLOR_BUFFER_BIT);
    }

    void FrameBuffer::setGLViewPort(GLsizei width, GLsizei height)
    {
        glViewport(0, 0, width, height);
    }

    void FrameBuffer::glDepthTest(bool enable)
    {
        if(enable == true)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }

    void FrameBuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->m_rendererID);
    }

    void FrameBuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
