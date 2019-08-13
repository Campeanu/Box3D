#ifndef __INDEX_BUFFER_HPP_INCLUDED__
#define __INDEX_BUFFER_HPP_INCLUDED__

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    #include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    #include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    #include <glad/glad.h>  // Initialize with gladLoadGL()
#else
    #include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "Box3D/Core.hpp"

namespace box3d {

    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        virtual ~IndexBuffer();

        void bind()   const;
        void unbind() const;

        inline unsigned int getCount() { return m_count; } 

    private:
        unsigned int m_rendererID;
        unsigned int m_count;
    };

}

#endif // !__INDEX_BUFFER_HPP_INCLUDED__