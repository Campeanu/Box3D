#ifndef __RENDERBUFFEROBJECT_INCLUDED__
#define __RENDERBUFFEROBJECT_INCLUDED__

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "Box3D/Application.hpp"

    namespace box3d {

        class RenderBufferObject
        {
        public:
            RenderBufferObject();
            virtual ~RenderBufferObject();

            void createStorage(box3d::Application& app);

            void bind()   const;
            void unbind() const;

            inline unsigned int getRendererID() { return this->m_rendererID; };

        private:
            unsigned int m_rendererID;
        };

    }

#endif // !__RENDERBUFFEROBJECT_INCLUDED__
