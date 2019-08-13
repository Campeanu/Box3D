#ifndef __VERTEXARRAY_HPP_INCLUDED__
#define __VERTEXARRAY_HPP_INCLUDED__

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace box3d {

    class VertexArray { 
    public: 
        VertexArray();
        virtual ~VertexArray();

    	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void bind()   const;
        void unbind() const;

    private:
        unsigned int m_rendererID;
    };

}

#endif // !__VERTEXARRAY_HPP_INCLUDED__