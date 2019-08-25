#ifndef __VERTEXBUFFER_LAYOUT__
#define __VERTEXBUFFER_LAYOUT__


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <vector>

namespace box3d {

    struct VertexBufferElement {

        unsigned int  type;
        unsigned int  count;
        unsigned char normalized;

        static unsigned int getSizeOfType(unsigned int type)
        {
            switch (type)
            {
                case GL_FLOAT: 		   return 4;
                case GL_UNSIGNED_INT:  return 4;
                case GL_UNSIGNED_BYTE: return 1;
            }
            return 0;
        }

    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout();
        virtual ~VertexBufferLayout();

        template<typename T>
        void push(unsigned int count)
        {
            static_assert(false);
        }

        template<>
        void push<float>(unsigned int count)
        {
            m_element.push_back({ GL_FLOAT, count, GL_FALSE });
            m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
        }

        template<>
        void push<unsigned int>(unsigned int count)
        {
            m_element.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
            m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
        }

        template<>
        void push<unsigned char>(unsigned int count)
        {
            m_element.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
            m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
        }

        inline const std::vector<VertexBufferElement> getElements() const& { return m_element; }
        inline unsigned int getStride() const& { return m_stride; }

    private:
        std::vector<VertexBufferElement> m_element;
        unsigned int m_stride;
    };

}

#endif // !__VERTEXBUFFER_LAYOUT__
