#ifndef __FRAMEBUFFER_HPP_INCLUDED__
#define __FRAMEBUFFER_HPP_INCLUDED__

#include <iostream>

#include "Box3D/Renderer/TextureBuffer.hpp"
#include "Box3D/Renderer/RenderBufferObject.hpp"

#include "Box3D/Application.hpp"

namespace box3d {

    class FrameBuffer {
    public:
        FrameBuffer();
        virtual ~FrameBuffer();

        void AddBuffer(box3d::RenderBufferObject& rbo, box3d::TextureBuffer& tcb, box3d::Application& app);
        void isComplete();
        void clear(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha, bool depth);
        void setGLViewPort(GLsizei width, GLsizei height);
        void glDepthTest(bool enable);

        void bind()   const;
        void unbind() const;

    private:
        unsigned int m_rendererID;
    };

}

#endif !__FRAMEBUFFER_HPP_INCLUDED__
